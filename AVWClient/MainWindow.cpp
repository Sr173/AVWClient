#include "MainWindow.hpp"
#include "ImplWindow.hpp"

MainWindow::MainWindow()
{
	size_ = { 800,600 };
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
	ImGui::ShowDemoWindow();
	ImGui::Begin(u8"Anti Virus 1.0",&isOpen, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize); {
		
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
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
		auto pos = ImGui::GetWindowPos();
		if (pos.x >= 1 || pos.y >= 1 || pos.x <= -1 || pos.y <= -1) {
			auto mainPos = ImplWindow::getPtr()->getpos();
			ImGui::SetWindowPos(ImVec2{ 0,0 });
			ImplWindow::getPtr()->pos(ImVec2(mainPos.x + pos.x, mainPos.y + pos.y));
		}
	}
	ImGui::End();
}
