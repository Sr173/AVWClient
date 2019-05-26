#pragma once
#include "WindowsBase.hpp"

class AVProcess : public WindowBase
{
public:
	virtual void pos(ImVec2 pos) {};
	virtual void size(ImVec2 pos) {};
	virtual void text(std::string txt) {};
	void render() override;
};

