#include "Websocket.hpp"
#include "iostream"

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

Websocket::Websocket(boost::asio::io_context& ioc)
	: resolver_(net::make_strand(ioc))
	, ws_(net::make_strand(ioc))
{
	
}

Websocket::~Websocket()
{


}

void Websocket::run(std::string ip, std::string port,std::string path)
{
	host_ = ip;
	port_ = port;
	path_ = path;

	// Look up the domain name
	resolver_.async_resolve(
		ip,
		port,
		beast::bind_front_handler(
			&Websocket::on_resolve,
			shared_from_this()));
}

void Websocket::run()
{
	run(host_, port_, path_);
}

void Websocket::on_resolve(beast::error_code ec, tcp::resolver::results_type results)
{
	if (ec)
		return fail(ec, "resolve");

	// Set the timeout for the operation
	beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

	// Make the connection on the IP address we get from a lookup
	beast::get_lowest_layer(ws_).async_connect(
		results,
		beast::bind_front_handler(
			&Websocket::on_connect,
			shared_from_this()));
}

void Websocket::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
{
	if (ec)
		return fail(ec, "connect");

	// Turn off the timeout on the tcp_stream, because
	// the websocket stream has its own timeout system.
	beast::get_lowest_layer(ws_).expires_never();

	// Set suggested timeout settings for the websocket
	ws_.set_option(
		websocket::stream_base::timeout::suggested(
			beast::role_type::client));

	// Set a decorator to change the User-Agent of the handshake
	ws_.set_option(websocket::stream_base::decorator(
		[](websocket::request_type & req)
		{
			req.set(http::field::user_agent,
				std::string(BOOST_BEAST_VERSION_STRING) +
				" websocket-client-async");
		}));

	// Perform the websocket handshake
	ws_.async_handshake(host_, path_,
		beast::bind_front_handler(
			&Websocket::on_handshake,
			shared_from_this()));
}

void Websocket::on_handshake(beast::error_code ec)
{
	if (ec)
		return fail(ec, "handshake");

	// Close the WebSocket connection
	ws_.async_read(
		buffer_,
		beast::bind_front_handler(
			&Websocket::on_read,
			shared_from_this()));
}

void Websocket::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
	if (ec) {
		return fail(ec, "read");
	}
	Notify<WebsocketObservers::WebsocketOnMessage>(
		std::string(static_cast<char*>(buffer_.data().data()), 
			buffer_.data().size())
		);
	buffer_.clear();
	ws_.async_read(
		buffer_,
		beast::bind_front_handler(
			&Websocket::on_read,
			shared_from_this()));
}

void Websocket::on_close(beast::error_code ec) const
{

}

void Websocket::fail(beast::error_code ec, char const* what) const
{
	std::cerr << what << ": [" <<  ec.value() << "]:" << ec.message() << " " << "\n";
}
