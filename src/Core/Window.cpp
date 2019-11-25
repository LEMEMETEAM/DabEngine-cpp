#include "GL/glew.h"
#include "Core/Window.hpp"
#include "Core/App.hpp"

void ogl_debug_callback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
    App::debugLog(HIGH, "0x%x 0x%x 0x%x %s\n", source, type, severity, message);
}

Window::Window(AppConfig& conf)
:m_handle(NULL), m_config(conf)
{
    App::debugLog("==Creating window==\n");
    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, 0);
    glfwWindowHint(GLFW_RESIZABLE, m_config.resizable ? 1 : 0);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //add mac

    if(m_config.debug)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    }

    if(m_config.fullscreenMode != NULL)
    {
        App::debugLog("Creating fullscreen window\n");
        glfwWindowHint(GLFW_REFRESH_RATE, m_config.fullscreenMode->refreshRate);
        m_handle = glfwCreateWindow(m_config.fullscreenMode->width, m_config.fullscreenMode->height, m_config.title, m_config.fullscreenMode->monitor.monitor, 0);
    }
    else
    {
        App::debugLog("Creating windowed window\n");
        glfwWindowHint(GLFW_DECORATED, m_config.decorated ? 1 : 0);
        m_handle = glfwCreateWindow(m_config.width, m_config.height, m_config.title, 0, 0);
    }
    if(!m_handle) App::debugLog("Window not created");
    App::debugLog("Making context\n");
    glfwMakeContextCurrent(m_handle);
    if(glewInit()){App::debugLog("GLEW Not Initialized\n");}
    glfwSwapInterval(m_config.vSync ? 1 : 0); 

    if(m_config.debug)
    {
        glDebugMessageCallback(ogl_debug_callback, 0);
    }
}

void Window::updateFramebufferInfo()
{
    glfwGetFramebufferSize(m_handle, &backBufferWidth, &backBufferHeight);
    glfwGetWindowSize(m_handle, &logicalWidth, &logicalHeight);

    m_config.width = logicalWidth;
    m_config.height = logicalHeight;
}

void Window::setTitle(const char* title)
{
    glfwSetWindowTitle(m_handle, title);
    m_config.title = title;
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
    return glfwGetWindowMonitor(m_handle) != NULL;
}

void Window::setWindowedMode(int width, int height)
{
    if(isFullscreen())
    {
        glfwSetWindowMonitor(m_handle, 0, 0, 0, width, height, 0);
    }
    else
    {
        glfwSetWindowSize(m_handle, width, height);
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

void Window::closeWindow(){glfwSetWindowShouldClose(m_handle, 1);}
bool Window::shouldClose(){return glfwWindowShouldClose(m_handle);}
void Window::showWindow(bool b){if(b) glfwShowWindow(m_handle); else glfwHideWindow(m_handle);}

Window::~Window()
{
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}
