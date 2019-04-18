#include "Application.hpp"
#include <windows.h>
#include "WindowsBase.hpp"

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
		Notify<ApplicationObservers::ApplicationEventLoopStart>();
		for (auto i : _allWindow) {
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
	_allWindow.push_back(window);
	return false;
}

bool Application::deleteRenderWindow(WindowBase* window)
{
	_allWindow.remove(window);
	return false;
}
