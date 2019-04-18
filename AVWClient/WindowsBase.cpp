#include "WindowsBase.hpp"
#include "Application.hpp"

WindowBase::WindowBase()
{
	Application::getPtr()->addRenderWindow(this);
}

WindowBase::~WindowBase()
{
	Application::getPtr()->deleteRenderWindow(this);
};
