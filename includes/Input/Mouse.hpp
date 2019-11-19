#ifndef MOUSE_H_
#define MOUSE_H_

#include "Events/Event.hpp"
#include "Events/EventListener.hpp"
#include "Events/EventSender.hpp"


class MouseMoveEvent : Event
{
    public:
        MouseMoveEvent(double&, double&, double&, double&);
        ~MouseMoveEvent(){}
        double getX(){return x;}
        double getY(){return y;}
        double getDeltaX(){return dx;}
        double getDeltaY(){return dy;}
    private:
        double x, y, dx, dy;
};

class MouseEvent : Event
{
    public:
        MouseEvent(int&, int, int&);
        ~MouseEvent(){}
        int getButton(){return button;}
        int getAction(){return action;}
        int getMod(){return mod;}
    private:
        int button, action, mod;
};

class MouseEventListener : EventListener
{
    public:
    virtual void onMouseButtonDown(MouseEvent&) = 0;
    virtual void onMouseButtonUp(MouseEvent&) = 0;
    virtual void onMouseMove(MouseMoveEvent&) = 0;
};

class Mouse : EventSender<MouseEventListener>
{
    public:
        void onMouseButtonDown(int&, int&);
        void onMouseButtonUp(int&, int&);
        void onMouseMove(double&, double&);
    private:
        double lastX, lastY;
};

#endif
