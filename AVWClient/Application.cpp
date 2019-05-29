#include "Application.hpp"
#include "WindowsBase.hpp"
#include <libgo/libgo.h>

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
		co_yield;
		if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			continue;
		}
		Notify<ApplicationObservers::ApplicationEventLoopStart>();
		ioc_.poll_one();
		for (auto i : all_window_) {
			if (i->is_show()) {
				i->render();
			}
		}
		if (!windowQueue.empty()) delete windowQueue.pop();
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

bool Application::addDeleteWindow(WindowBase* window)
{
	windowQueue.push_back(window);
	return false;
}

boost::asio::io_context* Application::get_io_context()
{
	return &ioc_;
}
