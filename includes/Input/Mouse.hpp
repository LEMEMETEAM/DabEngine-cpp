#ifndef MOUSE_H_
#define MOUSE_H_

class MouseEventListener : EventListener
{
    virtual void onMouseButtonDown(MouseEvent&) = 0;
    virtual void onMouseButtonUp(MouseEvent&) = 0;
    virtual void onMouseMove(MouseEvent&) = 0;
};

class MouseEvent
{
    public:
        MouseEvent(int&, int&, int&):
        int getButton();
        int getAction();
        int getMod();
    private:
        int button, action, mod;
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
