#include "GL/glew.h"
#include "GLFW/glfw3.h"

Window::Window(AppConfig& conf)
:m_handle(NULL), m_config(conf)
{
    App::debugLog("==Creating window==\n");
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, 0);
    glfwWindowHint(GLFW_RESIZABLE, config->resizable ? 1 : 0);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //add mac

    if(m_config.fullscreenMode != NULL)
    {
        App::debugLog("Creating fullscreen window\n");
        glfwWindowHint(GLFW_REFRESH_RATE, config->fullscreenMode->refreshRate);
        m_handle = glfwCreateWindow(m_config.fullscreenMode->width, m_config.fullscreenMode->height, m_config.title, m_config.fullscreenMode->monitor.monitor, 0);
    }
    else
    {
        App::debugLog("Creating windowed window\n");
        glfwWindowHint(GLFW_DECORATED, config->decorated ? 1 : 0);
        m_handle = glfwCreateWindow(m_config.width, m_config.height, m_config.title, 0, 0);
    }
    if(!win) (App::debugLog("Window not created"), return);
    App::debugLog("Making context\n");
    glfwMakeContextCurrent(m_handle);
    if(glewInit()){App::debugLog("GLEW Not Initialized\n"); return NULL;}
    glfwSwapInterval(config->vSync ? 1 : 0); 

    updateFramebufferInfo();
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

void Window::closeWindow(){glfwSetWindowShouldClose(windowHandle, 1);}
bool Window::shouldClose(){return glfwWindowShouldClose(windowHandle);}
void Window::showWindow(bool b){if(b) glfwShowWindow(windowHandle); else glfwHideWindow(windowHandle);}

Window::~Window()
{
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
}
