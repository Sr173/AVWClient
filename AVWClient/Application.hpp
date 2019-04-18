#pragma once
#include "IApplication.hpp"
#include "Singleton.hpp"
#include "Observer.hpp"

class WindowBase;

struct ApplicationObservers {
	enum { ApplicationCreateed, ApplicationEventLoopStart, ApplicationEventLoopEnd, ApplicationQuit };
	using ObserverTable = std::tuple<
		Observer<void()>,
		Observer<void()>, 
		Observer<void()>,
		Observer<void()>
	>;
};

class Application :
	public Observable<ApplicationObservers>,
	public IApplication,
	public Singleton<Application>
	{
public:
	void init();
	void exec() override;
	void quit();
	bool IsQuit() override;
	bool addRenderWindow(WindowBase* window);
	bool deleteRenderWindow(WindowBase* window);

protected:
	bool _isQuit = false;
	std::list<WindowBase*> _allWindow;
};
