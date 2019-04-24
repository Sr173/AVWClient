#pragma once
#include <string>
#include <boost/beast.hpp>
#include "Observer.hpp"

struct HttpReplyObservers {
	enum { HttpReplyFinished };
	using ObserverTable = std::tuple<
		Observer<void(std::string, boost::beast::error_code)>
	>;
};


class HttpReply : public Observable<HttpReplyObservers>
{
	friend class HttpWrapper;
public:
	boost::beast::error_code get_error_code();
private:
	void finished();
	std::string data_;
	boost::beast::error_code ec_;
	bool is_finished_ = false;
	HttpReply();
};