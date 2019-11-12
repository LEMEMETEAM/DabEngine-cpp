#ifndef WINDOW_H_
#define WINDOW_H_

class GLFWwindow;
class AppConfig;
class AppAdapter;

class Window
{

    public:
        static Window* createWindow(AppAdapter* adapter, AppConfig* conf);
        Window(GLFWwindow* handle, AppAdapter* adpt, AppConfig* conf):windowHandle(handle), adapter(adpt), config(conf){}
        ~Window();
        void init();

        void updateFramebufferInfo();
        GLFWwindow* getHandle(){return windowHandle;}
        AppAdapter* getAdapter(){return adapter;}
        void closeWindow();
        bool shouldClose();
        void showWindow(bool b);
    
    private:
        GLFWwindow* windowHandle;
        AppConfig* config;
        AppAdapter* adapter;
        int backBufferWidth, backBufferHeight;
        int logicalWidth, logicalHeight;
};

#endif