#include "ConfigWindow.h"
#include "Config.hpp"

ConfigWindow::ConfigWindow()
{
	text_ = u8"全局配置";
}

void ConfigWindow::render()
{
	ImGui::Begin(text_.c_str());
	int a[2] = {1,4};
	ImGui::SliderInt(u8"线程数量", &Config::getPtr()->thread_num, 1, 4);
	ImGui::End();
}
