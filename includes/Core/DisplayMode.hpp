#ifndef DISPLAYMODE_H_
#define DISPLAYMODE_H_

#include "Core/Monitor.hpp"

struct DisplayMode
{
    Monitor monitor;
    int width, height, refreshRate, bitsPerPixel;

    DisplayMode(Monitor& m, int w, int h, int r, int b) : monitor(m), width(w), height(h), refreshRate(r), bitsPerPixel(b){}
};

#endif