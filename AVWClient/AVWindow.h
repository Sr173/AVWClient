#pragma once
#include "WindowsBase.hpp"
#include "Singleton.hpp"

class AVWindow : public WindowBase ,public Singleton<AVWindow>
{
public:
	void render() override;
	virtual void pos(ImVec2 pos) {};
	virtual void size(ImVec2 pos) {};
	virtual void text(std::string txt)
	{
		text_ = txt;
	};
private:
	bool is_open_ = true;
};
