#ifndef WINDOW_H_
#define WINDOW_H_

class GLFWwindow;
class AppConfig;
class AppAdapter;
class Input;
struct Monitor;
struct DisplayMode;

class Window
{

    public:
        Window(AppConfig& conf);
        ~Window();

        void updateFramebufferInfo();

        GLFWwindow* getHandle(){return windowHandle;}
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
        GLFWwindow* windowHandle;
        AppConfig config;
        AppAdapter* adapter;
        int backBufferWidth, backBufferHeight;
        int logicalWidth, logicalHeight;
};

#endif
