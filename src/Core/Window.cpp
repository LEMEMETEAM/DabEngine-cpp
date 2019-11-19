#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Core/App.hpp"
#include "Core/Window.hpp"
#include "Core/AppConfig.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/Monitor.hpp"
#include "Core/DisplayMode.hpp"
#include "Core/Input.hpp"

Window::Window(GLFWwindow* handle, AppConfig* conf)
{
    this->windowHandle = handle;
    this->config = conf;
    this->input = new Input(this);
}

Window* Window::createWindow(AppConfig* config)
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
    glfwSwapInterval(config->vSync ? 1 : 0);
    
    return new Window(win, config);
}

void Window::init(AppAdapter* adapter)
{
    glfwSetWindowUserPointer(windowHandle, this);
    this->adapter = adapter;
    updateFramebufferInfo();
    glfwSetFramebufferSizeCallback(windowHandle, framebuffer_callback);
}

void Window::updateFramebufferInfo()
{
    glfwGetFramebufferSize(windowHandle, &backBufferWidth, &backBufferHeight);
    glfwGetWindowSize(windowHandle, &logicalWidth, &logicalHeight);

    config->width = logicalWidth;
    config->height = logicalHeight;
}

void Window::setTitle(const char* title)
{
    glfwSetWindowTitle(windowHandle, title);
    config->title = title;
}

int Window::getWidth(bool opengl = false)
{
    if(opengl) return backBufferWidth;
    else return logicalWidth;
}

int Window::getHeight(bool opengl = false)
{
    if(opengl) return backBufferHeight;
    else return logicalHeight;
}

bool Window::isFullscreen()
{
    return glfwGetWindowMonitor(windowHandle) != NULL;
}

void Window::setWindowedMode(int width, int height)
{
    if(isFullscreen())
    {
        glfwSetWindowMonitor(windowHandle, 0, 0, 0, width, height, 0);
    }
    else
    {
        glfwSetWindowSize(windowHandle, width, height);
    }
    updateFramebufferInfo();
}

Monitor* getMonitor()
{
    //TODO
    return NULL;
}

void setFullscreenMode(DisplayMode& mode)
{
    //TODO
}

void Window::onFrameBufferSizeChange(int width, int height)
{
    updateFramebufferInfo();
    adapter->resize(width, height);
    adapter->render();
    glfwSwapBuffers(windowHandle);
}

void Window::framebuffer_callback(GLFWwindow* win, int width, int height)
{
    Window* obj = static_cast<Window*>(glfwGetWindowUserPointer(win));
    obj->onFrameBufferSizeChange(width, height);
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