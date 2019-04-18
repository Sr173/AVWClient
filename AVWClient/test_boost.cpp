#include <tuple>
#include <utility>

#include <boost/signals2.hpp>


// Convenience wrapper for boost::signals2::signal.
template<typename Signature> class Observer {
public:
	Observer(const Observer&) = delete;
	Observer& operator=(const Observer&) = delete;
	Observer() = default;

private:
	template<typename Observers> friend class Observable;

	using Signal = boost::signals2::signal<Signature>;
	using SignalResult = typename Signal::result_type;

	Signal signal_;
};


// Generic observable mixin - users must derive from it.
template<typename Observers> class Observable {
private:
	using ObserverTable = typename Observers::ObserverTable;

public:
	// Registers an observer.
	template<size_t ObserverId, typename F>
	boost::signals2::connection
		Register(F&& f) {
		return std::get<ObserverId>(signals_).signal_.connect(std::forward<F>(f));
	}

protected:
	Observable() = default;

	// Notifies observers.
	template<size_t ObserverId, typename... Args>
	typename std::tuple_element<ObserverId, ObserverTable>::type::SignalResult
		Notify(Args&& ... args) const {
		return std::get<ObserverId>(signals_).signal_(std::forward<Args>(args)...);
	}

private:
	ObserverTable signals_;
};


//-----------------------------------------------------------------------------
// Example usage.
//-----------------------------------------------------------------------------

#include <iostream>


// Defines observers for Windows class.
struct WindowObservers {
	enum { ShowEvent, CloseEvent ,InitEvent};
	using ObserverTable = std::tuple<
		Observer<void()>,                 // ShowEvent
		Observer<bool(bool force_close)>,  // CloseEvent
		Observer<void()>
	>;
};


// Window: our Observable.
class Window : public Observable<WindowObservers> {
public:
	void Show() {
		std::cout << "Window::Show called." << std::endl;
		Notify<WindowObservers::ShowEvent>();
		std::cout << "Window::Show handled." << std::endl << std::endl;
	}

	bool Close(bool force_close = false) {
		std::cout << "Window::Close called: force_close == "
			<< std::boolalpha << force_close << "." << std::endl;

		const boost::optional<bool> can_close{
		  Notify<WindowObservers::CloseEvent>(force_close) };
		std::cout << "Window::Close handled. can_close == "
			<< std::boolalpha << (!can_close || *can_close) << "."
			<< std::endl << std::endl;

		const bool closing{ force_close || !can_close || *can_close };
		if (closing) {
			// Actually close the window.
			// ...  
		}
		return closing;
	}
	void Init() {
		Notify<WindowObservers::InitEvent>();
	}
};

// Application: our Observer.
class Application {
public:
	explicit Application(Window& window) : window_(window) {
		// Register window observers.
		window_.Register<WindowObservers::ShowEvent>([this]() {
			OnWindowShow();
			});
		window.Register<WindowObservers::CloseEvent>([this](bool force_close) {
			return OnWindowClose(force_close);
			});
		window.Register<WindowObservers::InitEvent>([this]() {
			return OnWindowInit();
			});
	}

private:
	void OnWindowShow() {
		std::cout << "Application::OnWindowShow called." << std::endl;
	}

	bool OnWindowClose(bool force_close) {
		std::cout << "Application::WindowClose called: force_close == "
			<< std::boolalpha << force_close << "." << std::endl;
		return force_close;
	}

	void OnWindowInit() {
		std::cout << "Init" << std::endl;
	}

	Window& window_;
};

#include "iostream"

void foo(int&& i) {
	i++;
}

void case11(int&& i) {
	foo(std::forward<int>(i));
}

void case12(int& i) {
	foo(std::forward<int>(i));
}

int main() {
	int i = 1;
	int& j = i;

	case11(std::forward<int>(i));
	std::cout << i << std::endl;
	case11(std::forward<int>(j));
	std::cout << i << std::endl;
	case12(std::forward<int&>(i));
	std::cout << i << std::endl;
	case12(std::forward<int&>(j));
	std::cout << i << std::endl;
}