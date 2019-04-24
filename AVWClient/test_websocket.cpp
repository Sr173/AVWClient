#include "Websocket.hpp"
#include "iostream"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>    
#include <boost/lexical_cast.hpp>


int main() {
	boost::asio::io_context ioc;
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	auto ws = std::make_shared<Websocket>(ioc);
	ws->run("127.0.0.1", "7777", boost::lexical_cast<std::string>(uuid));
	ws->Register<WebsocketObservers::WebsocketOnMessage>(
		[](std::string s) {
			std::cout << s << std::endl;
		}
	);
	ioc.run();
}
