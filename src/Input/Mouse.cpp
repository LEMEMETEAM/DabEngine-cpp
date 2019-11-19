#include "Input/Mouse.hpp"
#include "GLFW/glfw3.h"

MouseMoveEvent::MouseMoveEvent(double& x, double& y, double& dx, double& dy)
{
	this->x = x;
	this->y = y;
	this->dx = dx;
	this->dy = dy;
}

MouseEvent::MouseEvent(int& button, int action, int& mod)
{
	this->button = button;
	this->action = action;
	this->mod = mod;
}

void Mouse::onMouseButtonDown(int& button, int& mod)
{
	MouseEvent e(button, GLFW_PRESS, mod);
	for(MouseEventListener* l : listeners)
	{
		l->onMouseButtonDown(e);
	}
}

void Mouse::onMouseButtonUp(int& button, int& mod)
{
	MouseEvent e(button, GLFW_RELEASE, mod);
	for(MouseEventListener* l : listeners)
	{
		l->onMouseButtonUp(e);
	}
}

void Mouse::onMouseMove(double& x, double& y)
{
	double dx = x - lastX, dy = y - lastY;

	MouseMoveEvent e(x, y, dx, dy);
	for(MouseEventListener* l : listeners)
	{
		l->onMouseMove(e);
	}
}
