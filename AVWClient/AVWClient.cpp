// AVWClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CommonDefine.h"
#include <iostream>
#include "ImplWindow.hpp"
#include "Application.hpp"
#include "MainWindow.hpp"
#include <libgo/libgo.h>
#include "HttpWrapper.hpp"
#include "ClamAv.h"
#include "Websocket.hpp"

int main(int, char**)
{
	SetConsoleOutputCP(CP_UTF8);
	auto ptr = Application::getPtr();
	ImplWindow::getPtr()->text("Anti Virus 1.0");
	ImplWindow::getPtr()->size(ImVec2(800, 600));
	MainWindow::getPtr()->text("Anti Virus 1.0");
	MainWindow::getPtr()->size({ 0,0 });
	HttpWrapper::getPtr()->set_io_context(ptr->get_io_context());
	auto ws = std::make_shared<Websocket>(*ptr->get_io_context());
	ws->run("127.0.0.1", "80", "/ws");
	ws->Register<WebsocketObservers::WebsocketOnMessage>(
		[](std::string s) {
			std::cout << s << std::endl;
		}
	);

	auto post_reply = HttpWrapper::getPtr()->post("C:\\Users\\admin\\Personal\\pngpic\\62273861_p0-removebg.png", "127.0.0.1", "80");
	if (post_reply)
	{
		//post_reply->Register<HttpReplyObservers::HttpReplyFinished>([](std::string s)
		//{
		//		std::cout << s << std::endl;
		//});
	}


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


