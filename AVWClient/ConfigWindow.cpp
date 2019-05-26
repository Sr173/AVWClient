#include "ConfigWindow.h"
#include "Config.hpp"

ConfigWindow::ConfigWindow()
{
	text_ = u8"全局配置";
}

void ConfigWindow::render()
{
	static int select;
	static char local_path[_MAX_PATH] = "C:\\Users\\admin\\AppData\\Roaming\\ClamAv\\";
	static char remote_path[_MAX_PATH] = "127.0.0.1/api/db/all";
	static int scan_model = 0;

	ImGui::Begin(text_.c_str());
	ImGui::Text(u8"查毒模式:");
	ImGui::RadioButton(u8"本地模式", &select,0);
	ImGui::SameLine();
	if (select == 0) Config::getPtr()->runner_model = OffLine;
	ImGui::RadioButton(u8"云模式", &select, 1);
	if (select == 1) {
		Config::getPtr()->runner_model = Online;
		Config::getPtr()->thread_num = 1;
	}
	if (select == 0)
		ImGui::SliderInt(u8"线程数量", &Config::getPtr()->thread_num, 1, 4);
	else
		ImGui::SliderInt(u8"线程数量", &Config::getPtr()->thread_num, 1, 1);
	if (select == 0) {
		ImGui::InputText(u8"扫描引擎路径", local_path, _MAX_PATH);
		Config::getPtr()->db_uri = local_path;
	}
	else {
		ImGui::InputText(u8"扫描引擎地址", remote_path, _MAX_PATH);
		Config::getPtr()->db_uri = remote_path;
	}
	ImGui::Text(u8"扫描模式:");
	ImGui::BeginGroup();
	if (select == 0) {
		ImGui::RadioButton(u8"快速扫描", &scan_model, 1);
		Config::getPtr()->db_uri = remote_path;
		ImGui::SameLine();
	}
	if (select == 0 || select == 1) {
		ImGui::RadioButton(u8"完整扫描", &scan_model, 0);
		Config::getPtr()->db_uri = local_path;
	}
	const char* com_test[] = {
		u8"系统关键位置",
		u8"程序安装目录(X86_64)",
		u8"程序安装目录(X86)",
		u8"下载文件夹",
		u8"系统程序临时目录",
		u8"用户程序临时目录",
		u8"自定义"
	};
	static int select_scan_index = 0;
	ImGui::Combo(u8"扫描位置", &select_scan_index, com_test, 7);
	ImGui::EndGroup();
	static char scan_path_buffer[_MAX_PATH];
	switch (select_scan_index)
	{
	case 0:
		Config::getPtr()->scan_path = "C:\\windows\\";
		break;
	case 1:
		Config::getPtr()->scan_path = "C:\Program Files\\";
		break;	
	case 2:
		Config::getPtr()->scan_path = "C:\\Program Files (x86)\\";
	break;	
	case 3:
		Config::getPtr()->scan_path = "C:\\Users\\admin\\Downloads\\";
	break;	
	case 4:
		Config::getPtr()->scan_path = "C:\\ProgramData\\";
		break;
	case 5:
		Config::getPtr()->scan_path = "C:\\Users\\admin\\AppData\\";
		break;
	default:
		break;
	}
	if (select_scan_index <= 5)
	{
		ImGui::Text(u8"扫描目录:");
		ImGui::SameLine();
		ImGui::Text(Config::getPtr()->scan_path.data());
	}else
	{
		ImGui::InputText(u8"扫描目录", scan_path_buffer, _MAX_PATH);
		Config::getPtr()->scan_path = scan_path_buffer;
	}
	static int temp;
	ImGui::DragInt(u8"递归深度(-1代表无穷)", &temp, 1, -1, 10);
	ImGui::End();
}
