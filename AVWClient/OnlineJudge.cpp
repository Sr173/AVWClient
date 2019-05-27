#include "OnlineJudge.h"
#include "windows.h"
#include "Commdlg.h"

void OnlineJudge::render()
{
	ImGui::Begin(u8"云查杀");
	if (ImGui::Button(u8"选择文件")) {
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
		ofn.lpstrTitle = "请选择要扫描的文件";

		if (!GetOpenFileName(&ofn))
		{

		}
	} 
	ImGui::SameLine(); ImGui::Text(u8"请选择要查杀的文件");
	ImGui::Separator();
	ImGui::Text(u8"扫描进度");
	ImGui::ProgressBar(0.2); ImGui::SameLine(); ImGui::Text("正在进行第1/5个文件");
	ImGui::Separator();
	ImGui::Text(u8"服务器地址:127.0.0.1");
	ImGui::Text(u8"服务器连接状态:正常");
	ImGui::Text(u8"服务器已知病毒数量:4152361");

	ImGui::End();
}
