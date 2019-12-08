#ifndef MONITOR_H_
#define MONITOR_H_

#include "GLFW/glfw3.h"
#include <cstring>

struct Monitor
{
    GLFWmonitor* monitor;
    int virtualX, virtualY;
    const char* name;

    Monitor(GLFWmonitor* m, int vx, int vy, const char* n) : monitor(m), virtualX(vx), virtualY(vy), name(n){}  

    bool operator==(const Monitor& ref)
    {
        if(monitor == ref.monitor && virtualX == ref.virtualX  && virtualY == ref.virtualY && strcmp(name, ref.name))
        {
            return true;
        }
        return false;
    }  
};

#endif
