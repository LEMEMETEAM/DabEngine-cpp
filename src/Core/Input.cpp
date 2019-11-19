#include "Core/Input.hpp"
#include "Input/Keyboard.hpp"
#include "Input/Mouse.hpp"
#include "Core/Window.hpp"

Input::Input(Window* window)
{
	this->mouse = new Mouse();
	this->Keyboard = new new Keyboard();

	glfwSetKeyCallback(window->getHandle(), keyCallback);
	glfwSetMouseButtonCallback(window->getHandle(), mouseButtonCallback);
	glfwSetCursorPosCallback(window->getHandle(), cursorPosCallback);
}

Input::~Input()
{
	delete mouse;
	delete keyboard;
}

void Input::keyCallback(GLFWwindow* win, int key, int scancode, int action, int mod)
{
	switch(action)
	{
		case GLFW_RELEASE:
			keyboard.onKeyUp(key, scancode, mod);
			break;
		case GLFW_PRESS:
		case GFW_REPEAT:
			keyboard.onKeyDown(key, scancode, mod);
			break;
	}
}

void Input::mouseButtonCallback(GLFWwindow* win, int button, int action, int mod)
{
	switch(action)
	{
		case GLFW_RELEASE:
			mouse.onMouseButtonUp(button, mod);
			break;
		case GLFW_PRESS:
			mouse.onMouseButtonDown(button, mod);
			break;
	}
}

void Input::cursorPosCallback(GLFWwindow* win, double x, double y)
{
	mouse.onMouseMove(x, y);
}