#include "Skin.h"
#include "Application.hpp"

void Skin::render()
{
	bool is_opem;
	ImGui::Begin(u8"��������", &is_opem);
	ImGuiStyle& style = ImGui::GetStyle();
	static int style_idx = -1;
	if (ImGui::Combo(u8"���ڷ��", &style_idx, u8"�ŵ�\0��ɫ\0����\0"))
	{
		switch (style_idx)
		{
		case 0: ImGui::StyleColorsClassic(); break;
		case 1: ImGui::StyleColorsDark(); break;
		case 2: ImGui::StyleColorsLight(); break;
		}
	}
	ImGui::ColorPicker4("##picker", (float*)&Application::getPtr()->back_color,  ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);

	ImGui::End();
	if (!is_opem) delete_later();
}
