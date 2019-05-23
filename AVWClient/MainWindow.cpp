#include "MainWindow.hpp"
#include "ImplWindow.hpp"
#include "ConfigWindow.h"

MainWindow::MainWindow()
{
	size_ = { 800,600 };
	config_window_ = new ConfigWindow;
	config_window_->visible(false); 
}


MainWindow::~MainWindow()
{
}

void MainWindow::pos(ImVec2 pos)
{

}

void MainWindow::size(
	ImVec2 pos)
{

}

void MainWindow::text(std::string txt)
{
	this->text_ = txt;
}

void MainWindow::render()
{
	static bool isOpen = true;
	if (!isOpen) std::quick_exit(0);
	ImGui::Begin(u8"Anti Virus 1.0",&isOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize); {
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu(u8"文件"))
			{
				if (ImGui::MenuItem(u8"配置文件", "(A)")) {
					config_window_->visible(true);
				}
				if (ImGui::MenuItem("1", "1")) {
					MessageBox(0, 0, 0, 0);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Examples"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Help"))
			{

				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::SetWindowSize(text_.c_str(), { 800,0 });
		auto pos = ImGui::GetWindowPos();
		if (pos.x >= 1 || pos.y >= 1 || pos.x <= -1 || pos.y <= -1) {
			auto mainPos = ImplWindow::getPtr()->get_pos();
			ImGui::SetWindowPos(ImVec2{ 0,0 });
			ImplWindow::getPtr()->pos(ImVec2(mainPos.x + pos.x, mainPos.y + pos.y));
		}
	}
	ImGui::End();
}
