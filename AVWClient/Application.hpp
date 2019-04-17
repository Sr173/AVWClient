#pragma once
#include "IApplication.hpp"
#include "Singleton.hpp"

class Application : public IApplication,
	public Singleton<Application> {
public:
	void exec() override;
	bool IsQuit() override;
};
