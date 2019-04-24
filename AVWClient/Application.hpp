#pragma once
#include <boost/asio/io_context.hpp>
#include "IApplication.hpp"
#include "Singleton.hpp"
#include "Observer.hpp"

class WindowBase;
namespace boost {
	namespace asio{
	class io_context;
	};
};
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
	Application();
	void init();
	void exec() override;
	void quit();
	bool IsQuit() override;
	bool addRenderWindow(WindowBase* window);
	bool deleteRenderWindow(WindowBase* window);
	boost::asio::io_context* get_io_context();
protected:
	bool _isQuit = false;
	std::list<WindowBase*> all_window_;
	boost::asio::io_context ioc_;
};
