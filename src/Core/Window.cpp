#include "GL/glew.h"
#include "Core/Window.hpp"
#include "Core/App.hpp"
#include <algorithm>

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

Monitor toMonitor(GLFWmonitor* m)
{
    int x, y;
    glfwGetMonitorPos(m, &x, &y);
    const char* name = glfwGetMonitorName(m);
    return Monitor(m, x, y, name);
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

Monitor Window::getMonitor()
{
    std::vector<Monitor> ms = getMonitors();
    Monitor result = ms[0];

    int windowX, windowY, windowWidth, windowHeight;
    glfwGetWindowPos(m_handle, &windowX, &windowY);
    glfwGetWindowSize(m_handle, &windowWidth, &windowHeight);

    int overlap, bestOverlap = 0;
    for(Monitor m : ms)
    {
        DisplayMode mode = getDisplayMode(m);

        overlap = std::max(0,
                std::min(windowX + windowWidth, m.virtualX + mode.width)
                        - std::max(windowX, m.virtualX))
                * std::max(0, 
                std::min(windowY + windowHeight, m.virtualY + mode.height)
                - std::max(windowY, m.virtualY));
        
        if(bestOverlap < overlap)
        {
            bestOverlap = overlap;
            result = m;
        }
    }

    return result;
}

void Window::setFullscreenMode(DisplayMode& mode)
{
    if(isFullscreen())
    {
        Monitor m = getMonitor();
        DisplayMode current = getDisplayMode(m);
        if(current.monitor == mode.monitor && current.refreshRate == mode.refreshRate)
        {
            glfwSetWindowSize(m_handle, mode.width, mode.height);
        }
        else
        {
            glfwSetWindowMonitor(m_handle, mode.monitor.monitor, 0, 0, mode.width, mode.height, mode.refreshRate);
        }
    }
    else
    {
        glfwSetWindowMonitor(m_handle, mode.monitor.monitor, 0, 0, mode.width, mode.height, mode.refreshRate);
    }
    updateFramebufferInfo();
}

void Window::closeWindow(){glfwSetWindowShouldClose(m_handle, 1);}
bool Window::shouldClose(){return glfwWindowShouldClose(m_handle);}
void Window::showWindow(bool b){if(b) glfwShowWindow(m_handle); else glfwHideWindow(m_handle);}

std::vector<Monitor> Window::getMonitors()
{
    App::initGLFW();
    int count;
    GLFWmonitor** ms = glfwGetMonitors(&count);
    std::vector<Monitor> monitors;
    for(int i = 0; i < count; i++)
    {
        monitors.push_back(toMonitor(ms[i]));
    }
    return monitors;
}

Monitor Window::getPrimaryMonitor()
{
    App::initGLFW();
    return toMonitor(glfwGetPrimaryMonitor());
}

std::vector<DisplayMode> Window::getDisplayModes(Monitor& monitor)
{
    App::initGLFW();
    int count;
    const GLFWvidmode* vms = glfwGetVideoModes(monitor.monitor, &count);
    std::vector<DisplayMode> modes;
    for(int i = 0; i < count; i++)
    {
        GLFWvidmode vm = vms[i];
        modes.emplace_back(monitor, vm.width, vm.height, vm.refreshRate, vm.redBits+vm.greenBits+vm.blueBits);
    }
    return modes;
}

DisplayMode Window::getDisplayMode(Monitor& monitor)
{
    App::initGLFW();
    const GLFWvidmode* vm = glfwGetVideoMode(monitor.monitor);
    return DisplayMode(monitor, vm->width, vm->height, vm->refreshRate, vm->redBits+vm->greenBits+vm->blueBits);
}

Window::~Window()
{
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}
