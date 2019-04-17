#pragma once
#include <string>
#include "imgui_internal.h"
#include "imgui.h"

class WindowBase {
public:
	WindowBase() = default;
	virtual void begin() = 0;
	virtual void end() = 0;
	virtual void text(std::string& text) = 0;
	virtual std::string text() = 0;
	ImVec2 pos;
	ImVec2 size;
	std::string text;
	bool isShow;
protected:

};