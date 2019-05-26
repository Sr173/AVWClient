#pragma once
#include "HttpReply.hpp"
#include "Singleton.hpp"

namespace boost {
	namespace asio {
		class io_context;
	};
};

class HttpWrapper : public Singleton<HttpWrapper>
{
public:
	HttpReply* get(std::string host, std::string port, std::string path = "/",int timeout = 0);
	HttpReply* post(std::string file_path,std::string host, std::string port, std::string path = "/");
	void set_io_context(boost::asio::io_context* ioc);
private:
	boost::asio::io_context* ioc_;
};

