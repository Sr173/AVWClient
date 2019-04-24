#pragma once
#include "Singleton.hpp"
#include <tuple>
#include "Observer.hpp"
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>

struct WebsocketObservers {
	enum { WebsocketConnected, WebsocketDisconnected, WebsocketOnMessage };
	using ObserverTable = std::tuple<
		Observer<void()>,
		Observer<void()>,
		Observer<void(std::string)>
	>;
};

class Websocket : 
	public std::enable_shared_from_this<Websocket>,
	public Observable<WebsocketObservers>
{
public:
	Websocket(boost::asio::io_context& ioc);
	~Websocket();
	void run(std::string ip, std::string port, std::string uuid);
	void run();
private:
	void on_resolve(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type results);
	void on_connect(boost::beast::error_code ec, boost::asio::ip::tcp::resolver::results_type::endpoint_type);
	void on_handshake(boost::beast::error_code ec);
	void on_read(boost::beast::error_code ec, std::size_t bytes_transferred);
	void on_close(boost::beast::error_code ec);
	void fail(boost::beast::error_code ec, char const* what);

	boost::beast::websocket::stream<boost::beast::tcp_stream> ws_;
	boost::asio::ip::tcp::resolver resolver_;
	boost::beast::flat_buffer buffer_;

	std::string port_;
	std::string host_;
	std::string uuid_;
};

