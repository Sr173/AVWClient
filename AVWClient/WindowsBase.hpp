#pragma once
#include <string>
#include "imgui.h"

class WindowBase {
public:
	WindowBase();
	virtual ~WindowBase();
	virtual void render() = 0;
	virtual void pos(ImVec2 pos) = 0;
	virtual void size(ImVec2 pos) = 0;
	virtual void text(std::string txt) = 0;
	virtual ImVec2 get_pos() { return pos_; }
	virtual ImVec2 get_size() { return size_; }
	virtual std::string gettext() { return text_; }
	virtual void hidden() { is_show_ = false; }
	virtual void visible(bool b) { is_show_ = b; }
	virtual bool is_show() { return is_show_; }
protected:
	ImVec2 pos_ = { 0,0, };
	ImVec2 size_ = { 0,0 };
	std::string text_ = "";
	bool is_show_ = true;
};