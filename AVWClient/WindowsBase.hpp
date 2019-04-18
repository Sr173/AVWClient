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
	virtual ImVec2 getpos() { return _pos; }
	virtual ImVec2 getsize() { return _size; }
	virtual std::string gettext() { return _text; }
	virtual void hidden() { _isShow = false; }
	virtual bool isShow() { return _isShow; }
protected:
	ImVec2 _pos = { 0,0, };
	ImVec2 _size = { 0,0 };
	std::string _text = "";
	bool _isShow = true;
};