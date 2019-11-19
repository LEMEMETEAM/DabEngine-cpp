#include "Input/Keyboard.hpp"
#include "GLFW/glfw3.h"

KeyEvent::KeyEvent(int& key, int& scancode, int action, int& mod)
{
	this->key = key;
	this->scancode = scancode;
	this->action = action;
	this->mod = mod;
}

void Keyboard::onKeyDown(int& key, int& scancode, int& mod)
{
	KeyEvent e(key, scancode, GLFW_PRESS, mod);
	for(KeyEventListener* l : listeners)
	{
		l->onKeyDown(e);
	}
}

void Keyboard::onKeyUp(int& key, int& scancode, int& mod)
{
	KeyEvent e(key, scancode, GLFW_RELEASE, mod);
	for(KeyEventListener* l : listeners)
	{
		l->onKeyUp(e);
	}
}
