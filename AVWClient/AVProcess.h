#pragma once
#include "WindowsBase.hpp"
#include "Singleton.hpp"

class AVProcess : public WindowBase,public Singleton<AVProcess>
{
public:
	virtual void pos(ImVec2 pos) {};
	virtual void size(ImVec2 pos) {};
	virtual void text(std::string txt) {};
	void render() override;
};

