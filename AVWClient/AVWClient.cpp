// AVWClient.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "CommonDefine.h"
#include <iostream>
#include "ImplWindow.hpp"
#include "Application.hpp"
#include "MainWindow.hpp"

int main1(int, char**)
{
	auto ptr = Application::getPtr();;
	ImplWindow::getPtr()->text("Anti Virus 1.0");
	ImplWindow::getPtr()->size(ImVec2(800, 600));
	MainWindow::getPtr();
	ptr->exec();
	return 0;
}


