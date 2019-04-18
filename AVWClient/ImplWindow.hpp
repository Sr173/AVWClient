#pragma once
#include "Singleton.hpp"
#include "Observer.hpp"
#include "WindowsBase.hpp"
#include "imgui.h"
#include <windows.h>

class ImplWindow : 
	public WindowBase,
	public Singleton<ImplWindow>
{
public:
	ImplWindow();
	~ImplWindow();
	void newFrame();
	void endFrame();

	void pos(ImVec2 pos);
	void size(ImVec2 pos);
	void text(std::string txt);

	void render();
	static void ResetDevice();
	ImVec4 clear_color;
private:
	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	HWND hWnd;
};

