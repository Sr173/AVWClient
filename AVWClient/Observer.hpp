#include <boost/signals2.hpp>
#include <tuple>
#include <utility>

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
