#include "MainWindow.hpp"
#include "ImplWindow.hpp"
#include "ConfigWindow.h"
#include "Commdlg.h"
#include "AVWindow.h"
#include "AVProcess.h"

#pragma comment (lib,"Comdlg32.lib");

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
				if (ImGui::MenuItem(u8"加载本地数据库", "(A)")) {
					config_window_->visible(true);
				}
				if (ImGui::MenuItem("1", "1")) {
					MessageBox(0, 0, 0, 0);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu(u8"帮助"))
			{
				if (ImGui::MenuItem(u8"检查更新", "(C)")) {
				}
				if (ImGui::MenuItem(u8"关于我们", "(A)")) {
				}
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

	ImGui::Begin(u8"控制台");
	if (ImGui::Button(u8"开始杀毒"))
	{
		new AVProcess();
	}
	if(ImGui::Button(u8"加载扫描引擎"))
	{
		OPENFILENAMEA dialog = {0};
		OPENFILENAME ofn;
		char szFile[MAX_PATH];
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "*";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		ofn.lpstrTitle = "打开一个病毒引擎";

		if (!GetOpenFileName(&ofn))
		{

		}
	}
	static bool is_open_config = false;
	static bool is_open_result = false;

	ImGui::Checkbox(u8"打开配置文件窗口", &is_open_config);
	ImGui::Checkbox(u8"打开扫描结果窗口", &is_open_result);
	AVWindow::getPtr()->visible(is_open_result);

	ImGui::Text(u8"当前病毒库是否需要更新%s",u8"否"); //ImGui::SameLine(); ImGui::Button(u8"需要更新");
	ImGui::Text(u8"云查杀服务状态:%s",u8"已经连接");
	ImGui::Text(u8"加载的引擎数量:%d", 6);
	ImGui::Text(u8"已知病毒数量:%d", 512412);

	ImGui::End();
	ImGui::ShowDemoWindow();
}
