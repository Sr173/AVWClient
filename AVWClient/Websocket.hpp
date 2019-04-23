#pragma once
#include "Singleton.hpp"
#include <tuple>
#include "Observer.hpp"

struct WebsocketObservers {
	enum { WebsocketConnected, WebsocketDisconnected, WebsocketOnMessage };
	using ObserverTable = std::tuple<
		Observer<void()>,
		Observer<void()>,
		Observer<void(std::string)>,
	>;
};

class Websocket : 
	public Singleton<Websocket>,
	public Observable<WebsocketObservers>,
	public std::enable_shared_from_this<Websocket>
{
public:
	Websocket();
	~Websocket();
};

