#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core/App.hpp"
#include "Core/Window.hpp"
#include "Core/AppConfig.hpp"
#include "Core/AppAdapter.hpp"
#include <tuple>
#include <iostream>

static void framebuffer_callback(GLFWwindow* win, int width, int height)
{

}
Window* Window::createWindow(AppAdapter* adapter, AppConfig* config)
{

    App::debugLog("==Creating window==\n");
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, 0);
    glfwWindowHint(GLFW_RESIZABLE, config->resizable ? 1 : 0);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //add mac

    GLFWwindow* win;
    if(config->fullscreenMode != NULL)
    {
        App::debugLog("Creating fullscreen window\n");
        glfwWindowHint(GLFW_REFRESH_RATE, config->fullscreenMode->refreshRate);
        win = glfwCreateWindow(config->fullscreenMode->width, config->fullscreenMode->height, config->title, config->fullscreenMode->monitor.monitor, 0);
    }
    else
    {
        App::debugLog("Creating windowed window\n");
        glfwWindowHint(GLFW_DECORATED, config->decorated ? 1 : 0);
        win = glfwCreateWindow(config->width, config->height, config->title, 0, 0);
    }
    if(!win) return NULL;
    App::debugLog("Making context\n");
    glfwMakeContextCurrent(win);
    if(glewInit()){App::debugLog("GLEW Not Initialized\n"); return NULL;}
    glfwSwapInterval(config->vSync);
    
    return new Window(win, adapter, config);
}

void Window::init()
{
    updateFramebufferInfo();
    glfwSetWindowUserPointer(windowHandle, this);
    glfwSetFramebufferSizeCallback(windowHandle, [](GLFWwindow* win, int width, int height)
    {
        Window* ptr = static_cast<Window*>(glfwGetWindowUserPointer(win));
        ptr->updateFramebufferInfo();
        ptr->getAdapter()->resize(width, height);
        ptr->getAdapter()->render();
        glfwSwapBuffers(ptr->getHandle());
    });
}

void Window::updateFramebufferInfo()
{
    glfwGetFramebufferSize(windowHandle, &backBufferWidth, &backBufferHeight);
    glfwGetWindowSize(windowHandle, &logicalWidth, &logicalHeight);

    config->width = logicalWidth;
    config->height = logicalHeight;
}

void Window::closeWindow(){glfwSetWindowShouldClose(windowHandle, 1);}
bool Window::shouldClose(){return glfwWindowShouldClose(windowHandle);}
void Window::showWindow(bool b){if(b) glfwShowWindow(windowHandle); else glfwHideWindow(windowHandle);}

Window::~Window()
{
    
    glfwSetWindowUserPointer(windowHandle, NULL);
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
}