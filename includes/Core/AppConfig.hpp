#ifndef APPCONFIG_H_
#define APPCONFIG_H_

#include "Core/DisplayMode.hpp"

struct AppConfig
{
    const char* title = "";
    int width = 0, height = 0;
    int targetFPS = 60;
    bool resizable = false, decorated = true, vSync = false;
    DisplayMode* fullscreenMode = nullptr;

};

#endif