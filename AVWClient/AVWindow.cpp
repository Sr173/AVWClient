#include "AVWindow.h"
#include "AVScan.h"

void AVWindow::render()
{
	ImGui::Begin(u8"杀毒窗口");
	ImGui::Columns(6, u8"扫描结果"); // 4-ways, with border
	ImGui::Separator();
	ImGui::Text(u8"扫描编号"); ImGui::NextColumn();
	ImGui::Text(u8"文件路径"); ImGui::NextColumn();
	ImGui::Text(u8"字节数"); ImGui::NextColumn();
	ImGui::Text(u8"是否是病毒"); ImGui::NextColumn();
	ImGui::Text(u8"处理方式"); ImGui::NextColumn();
	ImGui::Text(u8"病毒名"); ImGui::NextColumn();

	ImGui::Separator();
	const char* names[] = { "RtlExUpd.exe", "WindowsShell.exe", "setupact.exe",u8"test.exe",u8"GGG.exe","aaaa.exe" };
	const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
	static int selected = -1;

	int index = 0;
	for (auto i : AVScan::getPtr()->get_virtus()) {
		char label[32];
		sprintf_s(label, "%04d", index);
		if (ImGui::Selectable(label, selected == index, ImGuiSelectableFlags_SpanAllColumns))
			selected = index;
		bool hovered = ImGui::IsItemHovered();
		ImGui::NextColumn();
		ImGui::Text(i.file_name.c_str()); ImGui::NextColumn();
		ImGui::Text("%d", i.scan_bytes); ImGui::NextColumn();
		ImGui::Text(u8"是"); ImGui::NextColumn();
		ImGui::Button(u8"删除文件"); ImGui::NextColumn();
		ImGui::Text(i.virus_name.c_str()); ImGui::NextColumn();
		index++;
	}
	ImGui::Columns(1);
	ImGui::Separator();
	ImGui::End();
}
