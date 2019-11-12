#include "Core/App.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/Window.hpp"
#include "Core/AppConfig.hpp"
#include "Utils/Timer.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
#include <cstdarg>

bool App::GLFWINIT = false;

void error_callback(int error, const char* description)
{   
    App::debugLog(HIGH, "GLFW Error %d: %s\n", error, description);
}

static void initGLFW()
{
    if(App::GLFWINIT) return;
    if(glfwInit() == GLFW_FALSE)
    {
        App::debugLog(HIGH, "Failed to Init GLFW\n");
    }

    glfwSetErrorCallback(error_callback);
    if(!App::GLFWINIT) App::GLFWINIT = true;
}

App::App(AppAdapter* a, AppConfig* conf)
{
    initGLFW();
    adapter = a;
    config = conf;

    window = Window::createWindow(a, config);
    if(!window){debugLog(HIGH, "Window not created\n");}

    window->init();

    a->connectApp(this);

    a->init();

    window->showWindow(true);
}

void App::run()
{
    double ns = 1.0/config->targetFPS;
    double acc = 0.0;
    Timer timer = Timer();

    while(!window->shouldClose())
    {
        timer.update();
        acc += timer.getDelta();
        while(acc >= ns)
        {
            adapter->update();
            glfwPollEvents();
            acc-=ns;
        }

        adapter->render();
        glfwSwapBuffers(window->getHandle());
    }


}

void App::debugLog(const char* text, ...)
{
    va_list args;
    va_start(args, text);

    debugLog(text, args);

    va_end(args);
    
}
void App::debugLog(int level, const char* text, ...)
{
    va_list args;
    va_start(args, text);

    debugLog(level, text, args);

    va_end(args);
}

void App::debugLog(int level, const char* text, va_list args)
{
    va_list a;
    va_copy(a, args);

    int num;
    switch(level)
    {
        case LOW:
            num = vfprintf(stdout, text, args);
            break;
        case HIGH:
            num = vfprintf(stderr, text, args);
            break;
    }

    va_end(a);
}

void App::debugLog(const char* text, va_list args)
{
    debugLog(LOW, text, args);
}

App::~App()
{
    debugLog("==App Shutdown==\n");

    debugLog("Free AppAdapter\n");
    delete adapter;
    adapter = NULL;

    debugLog("Free Config\n");
    config = NULL;

    debugLog("Free Window\n");
    delete window;
    window = NULL;

    debugLog("GoodBye o/");

}