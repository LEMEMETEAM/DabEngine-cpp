#include "GLFW/glfw3.h"

class Timer
{
    public:
        void update()
        {
            double time = getTime();
            deltatime = time - lasttime;
            lasttime = time;
        }

        double getTime()
        {
            return glfwGetTime();
        }

        double getDelta()
        {
            return deltatime;
        }

    private:
        double lasttime, deltatime;
};