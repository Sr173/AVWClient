#include "Application.hpp"
#include "WindowsBase.hpp"

using boost::asio::io_context;

Application::Application()
	: ioc_()
{
}

void Application::init()
{
	Notify<ApplicationObservers::ApplicationCreateed>();
}

void Application::exec()
{
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}
		ioc_.run_one();
		Notify<ApplicationObservers::ApplicationEventLoopStart>();
		for (auto i : all_window_) {
			if (i->isShow()) {
				i->render();
			}
		}
		Notify<ApplicationObservers::ApplicationEventLoopEnd>();
	}
	quit();
}

void Application::quit()
{
	_isQuit = true;
	Notify<ApplicationObservers::ApplicationQuit>();
	std::quick_exit(0);
}

bool Application::IsQuit()
{
	return _isQuit;
}

bool Application::addRenderWindow(WindowBase* window)
{
	all_window_.push_back(window);
	return false;
}

bool Application::deleteRenderWindow(WindowBase* window)
{
	all_window_.remove(window);
	return false;
}
