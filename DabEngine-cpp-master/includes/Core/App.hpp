#ifndef APP_H_
#define APP_H_

#include <cstdarg>

class Timer;
class Window;
class AppConfig;
class AppAdapter;

#define LOW 1
#define HIGH 2

class App
{

    public:
        static void debugLog(const char* text, ...);
        static void debugLog(int level, const char* text, ...);
        static void debugLog(const char* text, va_list args);
        static void debugLog(int level, const char* text, va_list args);
    public:
        App(AppAdapter* adapter, AppConfig* config);
        ~App();
        void run();
        AppAdapter* getAdapter(){return adapter;}
        AppConfig* getConfig(){return config;}
        static bool GLFWINIT;

    private:
        AppAdapter* adapter;
        AppConfig* config;
        Window* window;

};
#endif