#include "Skin.h"

void Skin::render()
{
	ImGui::Begin(u8"»»·ô´°¿Ú");
	ImGuiStyle& style = ImGui::GetStyle();

	static int output_dest = 0;
	static bool output_only_modified = true;
	if (ImGui::Button("Export Unsaved"))
	{
		if (output_dest == 0)
			ImGui::LogToClipboard();
		else
			ImGui::LogToTTY();
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const ImVec4& col = style.Colors[i];
			const char* name = ImGui::GetStyleColorName(i);
		}
		ImGui::LogFinish();
		
		ImGui::SameLine(); ImGui::PushItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0"); ImGui::PopItemWidth();
		ImGui::SameLine(); ImGui::Checkbox("Only Modified Colors", &output_only_modified);

		static ImGuiTextFilter filter;
		filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

		static ImGuiColorEditFlags alpha_flags = 0;
		ImGui::RadioButton("Opaque", &alpha_flags, 0); ImGui::SameLine();
		ImGui::RadioButton("Alpha", &alpha_flags, ImGuiColorEditFlags_AlphaPreview); ImGui::SameLine();
		ImGui::RadioButton("Both", &alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf); ImGui::SameLine();

		ImGui::BeginChild("##colors", ImVec2(0, 0), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
		ImGui::PushItemWidth(-160);
		for (int i = 0; i < ImGuiCol_COUNT; i++)
		{
			const char* name = ImGui::GetStyleColorName(i);
			if (!filter.PassFilter(name))
				continue;
			ImGui::PushID(i);
			ImGui::ColorEdit4("##color", (float*)& style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
			ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
			ImGui::TextUnformatted(name);
			ImGui::PopID();
		}
		ImGui::PopItemWidth();
		ImGui::EndChild();

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Fonts"))
	{
		ImGuiIO& io = ImGui::GetIO();
		ImFontAtlas* atlas = io.Fonts;
		ImGui::PushItemWidth(120);
		for (int i = 0; i < atlas->Fonts.Size; i++)
		{
			ImFont* font = atlas->Fonts[i];
			ImGui::PushID(font);
			bool font_details_opened = ImGui::TreeNode(font, "Font %d: \"%s\"\n%.2f px, %d glyphs, %d file(s)", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size, font->ConfigDataCount);
			ImGui::SameLine(); if (ImGui::SmallButton("Set as default")) { io.FontDefault = font; }
			if (font_details_opened)
			{
				ImGui::PushFont(font);
				ImGui::Text("The quick brown fox jumps over the lazy dog");
				ImGui::PopFont();
				ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
				ImGui::SameLine(); 
				ImGui::InputFloat("Font offset", &font->DisplayOffset.y, 1, 1, "%.0f");
				ImGui::Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
				ImGui::Text("Fallback character: '%c' (%d)", font->FallbackChar, font->FallbackChar);
				const float surface_sqrt = sqrtf((float)font->MetricsTotalSurface);
				ImGui::Text("Texture surface: %d pixels (approx) ~ %dx%d", font->MetricsTotalSurface, (int)surface_sqrt, (int)surface_sqrt);
				for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
					if (const ImFontConfig * cfg = &font->ConfigData[config_i])
						ImGui::BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d", config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH);
				if (ImGui::TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size))
				{
					// Display all glyphs of the fonts in separate pages of 256 characters
					for (int base = 0; base < 0x10000; base += 256)
					{
						int count = 0;
						for (int n = 0; n < 256; n++)
							count += font->FindGlyphNoFallback((ImWchar)(base + n)) ? 1 : 0;
						if (count > 0 && ImGui::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base + 255, count, count > 1 ? "glyphs" : "glyph"))
						{
							float cell_size = font->FontSize * 1;
							float cell_spacing = style.ItemSpacing.y;
							ImVec2 base_pos = ImGui::GetCursorScreenPos();
							ImDrawList* draw_list = ImGui::GetWindowDrawList();
							for (int n = 0; n < 256; n++)
							{
								ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size + cell_spacing), base_pos.y + (n / 16) * (cell_size + cell_spacing));
								ImVec2 cell_p2(cell_p1.x + cell_size, cell_p1.y + cell_size);
								const ImFontGlyph* glyph = font->FindGlyphNoFallback((ImWchar)(base + n));
								draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255, 255, 255, 100) : IM_COL32(255, 255, 255, 50));
								if (glyph)
									font->RenderChar(draw_list, cell_size, cell_p1, ImGui::GetColorU32(ImGuiCol_Text), (ImWchar)(base + n)); // We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions available to generate a string.
								if (glyph && ImGui::IsMouseHoveringRect(cell_p1, cell_p2))
								{
									ImGui::BeginTooltip();
									ImGui::Text("Codepoint: U+%04X", base + n);
									ImGui::Separator();
									ImGui::Text("AdvanceX: %.1f", glyph->AdvanceX);
									ImGui::Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
									ImGui::Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
									ImGui::EndTooltip();
								}
							}
							ImGui::Dummy(ImVec2((cell_size + cell_spacing) * 16, (cell_size + cell_spacing) * 16));
							ImGui::TreePop();
						}
					}
					ImGui::TreePop();
				}
				ImGui::TreePop();
			}
			ImGui::PopID();
		}
		if (ImGui::TreeNode("Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight))
		{
			ImGui::Image(atlas->TexID, ImVec2((float)atlas->TexWidth, (float)atlas->TexHeight), ImVec2(0, 0), ImVec2(1, 1), ImColor(255, 255, 255, 255), ImColor(255, 255, 255, 128));
			ImGui::TreePop();
		}

		static float window_scale = 1.0f;
		if (ImGui::DragFloat("this window scale", &window_scale, 0.005f, 0.3f, 2.0f, "%.2f"))   // scale only this window
			ImGui::SetWindowFontScale(window_scale);
		ImGui::DragFloat("global scale", &io.FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.2f");      // scale everything
		ImGui::PopItemWidth();

		ImGui::EndTabItem();
	}
	ImGui::End();
}
