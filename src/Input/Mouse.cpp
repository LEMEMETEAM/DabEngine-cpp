#include "Input/Mouse.hpp"
#include "GLFW/glfw3.h"

MouseMoveEvent::MouseMoveEvent(double _x, double _y, double _dx, double _dy)
:x(_x), y(_y), dx(_dx), dy(_dy)
{}

MouseEvent::MouseEvent(int _button, int _action, int _mod)
:button(_button), action(_action), mod(_mod)
{}

void Mouse::onMouseButtonDown(int button, int mod)
{
	MouseEvent e(button, GLFW_PRESS, mod);
	for(std::vector<MouseEventListener>::iterator it = listeners.begin(); it < listeners.end(); it++)
	{
		it->onMouseButtonDown(e);
	}
}

void Mouse::onMouseButtonUp(int button, int mod)
{
	MouseEvent e(button, GLFW_RELEASE, mod);
	for(std::vector<MouseEventListener>::iterator it = listeners.begin(); it < listeners.end(); it++)
	{
		it->onMouseButtonUp(e);
	}
}

void Mouse::onMouseMove(double x, double y)
{
	double dx = x - lastX, dy = y - lastY;

	MouseMoveEvent e(x, y, dx, dy);
	for(std::vector<MouseEventListener>::iterator it = listeners.begin(); it < listeners.end(); it++)
	{
		it->onMouseMove(e);
	}
}
