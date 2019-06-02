#pragma once
#include "WindowsBase.hpp"
#include "Singleton.hpp"

class LocalEngine;

class MainWindow : public WindowBase , public Singleton<MainWindow>
{
public:
	MainWindow();
	~MainWindow();
	virtual void pos(ImVec2 pos);
	virtual void size(ImVec2 pos);
	virtual void text(std::string txt);
	virtual void render();
private:
	LocalEngine* engine;
};

