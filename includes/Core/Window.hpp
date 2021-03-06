#ifndef WINDOW_H_
#define WINDOW_H_

#include "GLFW/glfw3.h"
#include "Core/AppConfig.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/Monitor.hpp"
#include "Core/DisplayMode.hpp"
#include <vector>

class Window
{

    public:
        Window(AppConfig& conf);
        ~Window();

        void updateFramebufferInfo();

        GLFWwindow* getHandle(){return m_handle;}
        int getWidth(bool opengl = false);
        int getHeight(bool opengl = false);
        bool isFullscreen();
        Monitor getMonitor();

        void setWindowedMode(int width, int height);
        void setFullscreenMode(DisplayMode& mode);
        void setTitle(const char* title);
        void closeWindow();
        bool shouldClose();
        void showWindow(bool b);

        static std::vector<Monitor> getMonitors();
        static Monitor getPrimaryMonitor();
        static std::vector<DisplayMode> getDisplayModes(Monitor& monitor);
        static DisplayMode getDisplayMode(Monitor& monitor);
    
    private:
        GLFWwindow* m_handle;
        AppConfig m_config;
        int backBufferWidth, backBufferHeight;
        int logicalWidth, logicalHeight;
};

#endif
