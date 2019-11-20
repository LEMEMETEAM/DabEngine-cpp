#ifndef WINDOW_H_
#define WINDOW_H_

#include "GLFW/glfw3.h"
#include "Core/AppConfig.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/Monitor.hpp"
#include "Core/DisplayMode.hpp"

class Window
{

    public:
        Window(AppConfig& conf);
        ~Window();

        void updateFramebufferInfo();

        GLFWwindow* getHandle(){return m_handle;}
        int getWidth(bool opengl);
        int getHeight(bool opengl);
        bool isFullscreen();
        Monitor* getMonitor();

        void setWindowedMode(int width, int height);
        void setFullscreenMode(DisplayMode& mode);
        void setTitle(const char* title);
        void closeWindow();
        bool shouldClose();
        void showWindow(bool b);
    
    private:
        GLFWwindow* m_handle;
        AppConfig m_config;
        int backBufferWidth, backBufferHeight;
        int logicalWidth, logicalHeight;
};

#endif
