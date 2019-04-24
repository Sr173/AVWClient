#include "HttpReply.hpp"

boost::beast::error_code HttpReply::get_error_code()
{
	return ec_;
}

void HttpReply::finished()
{
	is_finished_ = true;
	Notify<HttpReplyObservers::HttpReplyFinished>(std::move(data_), ec_);
	delete this;
}

HttpReply::HttpReply()
{
	ec_ = boost::beast::make_error_code(boost::beast::error::timeout);
}

