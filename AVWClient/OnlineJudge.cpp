#include "OnlineJudge.h"

void OnlineJudge::render()
{
	ImGui::Begin(u8"云查杀");
	ImGui::Button(u8"选择文件"); ImGui::SameLine(); ImGui::Text(u8"请选择要查杀的文件");
	ImGui::Separator();
	ImGui::Text(u8"扫描进度");
	ImGui::ProgressBar(0.2); ImGui::SameLine(); ImGui::Text("正在进行第1/5个文件");
	ImGui::Separator();
	ImGui::Text(u8"服务器地址:127.0.0.1");
	ImGui::Text(u8"服务器连接状态:正常");
	ImGui::Text(u8"服务器已知病毒数量:正常");

	ImGui::End();
}
