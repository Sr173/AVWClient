// AVWClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CommonDefine.h"
#include <iostream>
#include "ImplWindow.hpp"
#include "Application.hpp"
#include "MainWindow.hpp"
#include <libgo/libgo.h>
#include "HttpWrapper.hpp"

int main(int, char**)
{
	auto ptr = Application::getPtr();
	ImplWindow::getPtr()->text("Anti Virus 1.0");
	ImplWindow::getPtr()->size(ImVec2(800, 600));
	MainWindow::getPtr()->text("Anti Virus 1.0");
	HttpWrapper::getPtr()->set_io_context(ptr->get_io_context());
	auto reply = HttpWrapper::getPtr()->get("127.0.0.1", "80");
	reply->Register<HttpReplyObservers::HttpReplyFinished>([](std::string s,boost::beast::error_code ec) {
		std::cout << s;
		std::cout << ec;
		});

	go std::bind(&Application::exec, ptr);
	go[]() {
		for (int i = 0; i < 100; i++) {
			std::cout << i << std::endl;
			co_sleep(100);
		}
	};
	g_Scheduler.Start();
	return 0;
}


