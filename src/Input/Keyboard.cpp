#include "Input/Keyboard.hpp"
#include "GLFW/glfw3.h"

KeyEvent::KeyEvent(int _key, int _scancode, int _action, int _mod)
:key(_key), scancode(_scancode), action(_action), mod(_mod)
{}

void Keyboard::onKeyDown(int key, int scancode, int mod)
{
	KeyEvent e(key, scancode, GLFW_PRESS, mod);
	for(std::vector<KeyEventListener>::iterator it = listeners.begin(); it < listeners.end(); it++)
	{
		it->onKeyDown(e);
	}
}

void Keyboard::onKeyUp(int key, int scancode, int mod)
{
	KeyEvent e(key, scancode, GLFW_RELEASE, mod);
	for(std::vector<KeyEventListener>::iterator it = listeners.begin(); it < listeners.end(); it++)
	{
		it->onKeyUp(e);
	}
}
