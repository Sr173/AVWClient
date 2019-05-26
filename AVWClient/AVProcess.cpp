#include "AVProcess.h"
#include <vector>
#include <time.h>
#include <windows.h>
#include <algorithm>

#define max max

void AVProcess::render()
{
	static int num = 0;
	static std::vector<float> data(90);
	static auto last_time = GetTickCount64();

	int delay_time = last_time - GetTickCount64();
	if (delay_time == 0) delay_time = 25;
	int frame_data = rand() % 100000 + 500 * (1000 / delay_time );

	if (data.size() > 90)
	{
		auto temp_data = data;
		data.clear();
		data.push_back(frame_data);
		temp_data.pop_back();
		for (auto i : temp_data)
			data.push_back(i);
	}
	else
	{
		data.push_back(frame_data);

	}
	
	ImGui::Begin(u8"扫描进度");
	std::vector<float> file_count;
	static char num_buffer[50];
	sprintf_s(num_buffer, u8"每秒扫描字节数%d", int(frame_data));
	static float arr[] = {0.f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
	ImGui::PlotLines(u8"每秒扫描文件数:68", arr, IM_ARRAYSIZE(arr));
	ImGui::PlotLines(num_buffer, data.data(), data.size(), 0, "avg 0.0", -1, *std::max_element(data.begin(), data.end())+ 1, ImVec2(0, 80));
	ImGui::Text(u8"线程1正在扫描文件:%s", u8"C:\\Windows\\driver\\splwow64.exe");
	ImGui::Text(u8"线程2正在扫描文件:%s", u8"C:\\Windows\\driver\\regedit.exe");
	ImGui::Text(u8"线程3正在扫描文件:%s", u8"C:\\Windows\\driver\\pyw.exe");
	ImGui::Text(u8"线程4正在扫描文件:%s", u8"C:\\Windows\\driver\\py.exe");
	ImGui::Separator();
	ImGui::Text(u8"当前扫描文件夹:C:\\windows\\driver\\");
	ImGui::ProgressBar(0.782, ImVec2(0.f, 0.f), u8"782/1000"); ImGui::SameLine(); ImGui::Text(u8"此文件夹扫描进度");
	ImGui::Separator();
	ImGui::Text(u8"共扫描文件%d个", 19920);
	ImGui::Text(u8"发现病毒%d个", 0);
	ImGui::End();
}
