#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include "coroutine.h"



#pragma comment (lib,"ws2_32.lib")
#pragma comment (lib,"G:\\bysj\\libgo\\lib\\libgo_MDD_X64.lib")
#pragma comment (lib,"libboost_date_time-vc142-mt-gd-x64-1_70.lib")

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

// Sends a WebSocket message and prints the response
int main111111111(int argc, char** argv)
{
	try
	{
		auto const host = "127.0.0.1";
		auto const port = "7777";
		auto const text = "ping";

		// The io_context is required for all I/O
		net::io_context ioc;

		// These objects perform our I/O
		tcp::resolver resolver{ ioc };
		websocket::stream<tcp::socket> ws{ ioc };

		// Look up the domain name
		auto const results = resolver.resolve(host, port);

		// Make the connection on the IP address we get from a lookup
		net::connect(ws.next_layer(), results.begin(), results.end());

		// Set a decorator to change the User-Agent of the handshake
		ws.set_option(websocket::stream_base::decorator(
			[](websocket::request_type & req)
			{
				req.set(http::field::user_agent,
					std::string(BOOST_BEAST_VERSION_STRING) +
					" websocket-client-coro");
			}));

		// Perform the websocket handshake
		ws.handshake(host, "/");

		// Send the message
		ws.write(net::buffer(std::string(text)));

		// This buffer will hold the incoming message
		beast::flat_buffer buffer;
		g_Scheduler.goStart(4, 0);

		// Read a message into our buffer
		for (int i = 0; i < 100; i++) {
			ws.read(buffer);
			std::cout << beast::make_printable(buffer.data()) << std::endl;
		}
		while (!g_Scheduler.IsEmpty()) {
		}
		// Close the WebSocket connection

		// If we get here then the connection is closed gracefully

		// The make_printable() function helps print a ConstBufferSequence
		ws.close(websocket::close_code::normal);

	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}