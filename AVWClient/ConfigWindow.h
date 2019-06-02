#pragma once
#include "WindowsBase.hpp"
#include "Singleton.hpp"

class ConfigWindow : public WindowBase ,public Singleton<ConfigWindow>{
public:
	ConfigWindow();
	void render() override;
	virtual void pos(ImVec2 pos){};
	virtual void size(ImVec2 pos){};
	virtual void text(std::string txt)
	{
		text_ = txt;
	};
};

