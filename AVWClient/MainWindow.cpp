#include "MainWindow.hpp"
#include "ImplWindow.hpp"

MainWindow::MainWindow()
{

}


MainWindow::~MainWindow()
{
}

void MainWindow::pos(ImVec2 pos)
{

}

void MainWindow::size(ImVec2 pos)
{
}

void MainWindow::text(std::string txt)
{
}

void MainWindow::render()
{
	static bool isOpen = false;

	ImGui::Begin(u8"Anti Virus 1.0",&isOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_::ImGuiWindowFlags_MenuBar); {
		ImGui::BeginMainMenuBar();
		ImGui::MenuItem("1", "1" );
		ImGui::EndMainMenuBar();

		auto pos = ImGui::GetWindowPos();
		if (pos.x >= 1 || pos.y >= 1 || pos.x <= 1 || pos.y <= 1) {
			auto mainPos = ImplWindow::getPtr()->getpos();
			ImGui::SetWindowPos(ImVec2{ 0,0 });
			ImplWindow::getPtr()->pos(ImVec2(mainPos.x + pos.x, mainPos.y + pos.y));
		}
		ImGui::Button(u8"开始杀毒");
	}
	ImGui::End();
}
