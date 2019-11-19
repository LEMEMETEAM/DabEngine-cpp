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
        static Window* createWindow(AppConfig* conf);
        Window(GLFWwindow* handle, AppConfig* conf);
        ~Window();
        void init(AppAdapter* adapter);

        void updateFramebufferInfo();

        GLFWwindow* getHandle(){return windowHandle;}
        Input* getInput(){return input;}
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
        void onFrameBufferSizeChange(int width, int height);
        static void framebuffer_callback(GLFWwindow* win, int width, int height);
        GLFWwindow* windowHandle;
        AppConfig* config;
        Input* input;
        AppAdapter* adapter;
        int backBufferWidth, backBufferHeight;
        int logicalWidth, logicalHeight;
};

#endif