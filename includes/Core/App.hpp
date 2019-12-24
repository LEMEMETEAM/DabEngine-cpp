#ifndef APP_H_
#define APP_H_

#include <cstdarg>
#include "Core/AppConfig.hpp"
#include "Core/Window.hpp"

#define LOW 1
#define HIGH 2

class AppAdapter;
class Mouse;
class Keyboard;

class App
{

    public:
        static void debugLog(const char* text, ...);
        static void debugLog(int level, const char* text, ...);
        static void debugLog(const char* text, va_list args);
        static void debugLog(int level, const char* text, va_list args);
        static void initGLFW();
    public:
        App(AppAdapter* adapter, AppConfig& config);
        ~App();
        void run();
        AppAdapter* getAdapter(){return m_adapter;}
        AppConfig& getConfig(){return m_config;}
        Window& getWindow(){return m_window;}
        Mouse* getMouse(){return m_mouse;}
        Keyboard* getKeyboard(){return m_keyboard;}

        static bool GLFWINIT;

    private:
        AppAdapter* m_adapter;
        AppConfig m_config;
        Mouse* m_mouse = new Mouse();
        Keyboard* m_keyboard = new Keyboard();
        Window m_window;

};
#endif
