#include "Core/App.hpp"
#include "Utils/Timer.hpp"
#include "GLFW/glfw3.h"
#include <iostream>

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

static void framebuffer_callback(GLFWwindow* win, int width, int height)
{
    App* ptr = static_cast<App*>(glfwGetWindowUserPointer(win));
    ptr->getWindow().updateFramebufferInfo();
    ptr->getAdapter()->resize(width, height);
    ptr->getAdapter()->render();
    glfwSwapBuffers(win);
}

App::App(AppAdapter* a, AppConfig& conf)
:m_adapter(a), m_config(conf), m_window((initGLFW(), conf))
{

    //create callbacks
    glfwSetWindowUserPointer(m_window.getHandle(), this);
    glfwSetFramebufferSizeCallback(m_window.getHandle(), framebuffer_callback);

    m_adapter->connectApp(this);

    m_adapter->init();

    m_window.showWindow(true);
}

void App::run()
{
    double ns = 1.0/m_config.targetFPS;
    double acc = 0.0;
    Timer timer = Timer();

    while(!m_window.shouldClose())
    {
        timer.update();
        acc += timer.getDelta();
        while(acc >= ns)
        {
            m_adapter->update();
            glfwPollEvents();
            acc-=ns;
        }

        m_adapter->render();
        glfwSwapBuffers(m_window.getHandle());
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
    delete m_adapter;
    m_adapter = nullptr;

    debugLog("GoodBye o/");

}
