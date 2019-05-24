#include "ConfigWindow.h"
#include "Config.hpp"

ConfigWindow::ConfigWindow()
{
	text_ = u8"全局配置";
}

void ConfigWindow::render()
{
	static int select;

	ImGui::Begin(text_.c_str());
	ImGui::RadioButton(u8"本地模式", &select,0);
	ImGui::SameLine();
	if (select == 0) Config::getPtr()->runner_model = OffLine;
	ImGui::RadioButton(u8"云模式", &select, 1);
	if (select == 1) Config::getPtr()->runner_model = Online;
	int a[2] = {1,4};
	ImGui::SliderInt(u8"线程数量", &Config::getPtr()->thread_num, 1, 4);
	ImGui::End();
}
