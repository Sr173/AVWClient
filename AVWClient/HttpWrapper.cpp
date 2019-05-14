#include "HttpWrapper.hpp"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include "../thrty_party/libgo/libgo.h"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

HttpReply* HttpWrapper::get(std::string host, std::string port, std::string path,int timeout)
{
	auto reply = new HttpReply;
	go[=]() {
		try {
			go[&]() {
				if (timeout) co_sleep(timeout);
				else return;
				if (!reply->is_finished_) delete reply;
			};
			tcp::resolver resolver(*ioc_);
			beast::tcp_stream stream(*ioc_);
			auto const results = resolver.resolve(host, port);
			stream.connect(results);
			http::request<http::string_body> req{ http::verb::get, path, 10 };
			req.set(http::field::host, host);
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			http::write(stream, req);
			beast::flat_buffer buffer;
			http::response<http::dynamic_body> res;
			http::read(stream, buffer, res);
			beast::error_code ec;
			stream.socket().shutdown(tcp::socket::shutdown_both, ec);
			if (ec && ec != beast::errc::not_connected)
				throw beast::system_error{ ec };
			int size = buffer.data().size();
			std::cout << res << std::endl;
			reply->data_ = beast::buffers_to_string(res.body().data());
			reply->ec_ = ec;
			reply->finished();
		}
		catch (std::exception const& e)
		{
			std::cout << e.what() << std::endl;
			//reply->ec_ = e.code();
		}
	};
	return reply;
}

HttpReply* HttpWrapper::post(std::string host, std::string port, std::string path)
{
	return nullptr;
}

void HttpWrapper::set_io_context(boost::asio::io_context* ioc)
{
	ioc_ = ioc;
}
