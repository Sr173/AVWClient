#pragma once

class IApplication {
public:
	IApplication() = default;
	virtual bool IsQuit() = 0;
	virtual void exec() = 0;
	virtual ~IApplication() = default;
};