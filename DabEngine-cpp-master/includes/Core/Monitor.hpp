#ifndef MONITOR_H_
#define MONITOR_H_

class GLFWmonitor;

struct Monitor
{
    GLFWmonitor* monitor;
    int virtualX, virtualY;
    char* name;

    Monitor(GLFWmonitor* m, int vx, int vy, char* n) : monitor(m), virtualX(vx), virtualY(vy), name(n){}    
};

#endif