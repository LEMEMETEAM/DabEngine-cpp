#ifndef INPUT_H_
#define INPUT_H_

#include "GLFW/glfw3.h"

class Keyboard;
class Mouse;
class Window;

class Input
{
	public:
		Input(Window* window);
		~Input();
		Keyboard* getKeyboard(){return keyboard;}
		Mouse* getMouse(){return mouse;}
	private:
		static void keyCallback(GLFWwindow* win, int key, int scancode, int action, int mod);
		static void mouseButtonCallback(GLFWwindow* win, int button, int action, int mod);
		static void cursorPosCallback(GLFWwindow* win, double x, double y);
		Mouse* mouse;
		Keyboard* keyboard;
};

#endif