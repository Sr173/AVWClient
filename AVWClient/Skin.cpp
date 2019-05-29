#include "Skin.h"
#include "Application.hpp"

void Skin::render()
{
	bool is_opem;
	ImGui::Begin(u8"换肤窗口", &is_opem);
	ImGuiStyle& style = ImGui::GetStyle();
	static int style_idx = -1;
	if (ImGui::Combo(u8"窗口风格", &style_idx, u8"古典\0暗色\0明亮\0"))
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
