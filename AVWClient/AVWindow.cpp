#include "AVWindow.h"

void AVWindow::render()
{
	ImGui::Begin(u8"杀毒窗口");
	ImGui::Columns(10, u8"扫描结果"); // 4-ways, with border
	ImGui::Separator();
	ImGui::Text(u8"扫描编号"); ImGui::NextColumn();
	ImGui::Text(u8"文件路径"); ImGui::NextColumn();
	ImGui::Text(u8"字节数"); ImGui::NextColumn();
	ImGui::Text(u8"是否是病毒"); ImGui::NextColumn();
	ImGui::Text(u8"处理方式"); ImGui::NextColumn();
	ImGui::Text(u8"引擎1扫描结果"); ImGui::NextColumn();
	ImGui::Text(u8"引擎2扫描结果"); ImGui::NextColumn();
	ImGui::Text(u8"引擎3扫描结果"); ImGui::NextColumn();
	ImGui::Text(u8"引擎4扫描结果"); ImGui::NextColumn();
	ImGui::Text(u8"引擎5扫描结果"); ImGui::NextColumn();

	ImGui::Separator();
	const char* names[] = { "RtlExUpd.exe", "WindowsShell.exe", "setupact.exe",u8"test.exe",u8"GGG.exe","aaaa.exe" };
	const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
	static int selected = -1;
	for (int i = 0; i < 5; i++)
	{
		char label[32];
		sprintf_s(label, "%04d", i);
		if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
			selected = i;
		bool hovered = ImGui::IsItemHovered();
		ImGui::NextColumn();
		ImGui::Text(names[rand() % 5]); ImGui::NextColumn();
		ImGui::Text("%d", rand() % 100000 + 10000); ImGui::NextColumn();
		ImGui::Text(u8"是"); ImGui::NextColumn();
		ImGui::Button(u8"删除文件"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text(u8"是"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
	}
	for (int i = 0; i < 100; i++)
	{
		char label[32];
		sprintf_s(label, "%04d", i + 5);
		if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
			selected = i;
		ImGui::NextColumn();
		ImGui::Text(names[rand() % 5]); ImGui::NextColumn();
		ImGui::Text("%d", rand() % 100000 + 10000); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text(u8"无"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text("否"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
		ImGui::Text(u8"否"); ImGui::NextColumn();
	}
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::End();
}
