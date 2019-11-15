#ifndef KEYBOARD_H_
#define KEYBOARD_H_

class KeyEvent
{
    public:
        MouseEvent(int&, int&, int&, int&):
        int getKey();
        int getScancode();
        int getAction();
        int getMod();
    private:
        int key, scancode, action, mod;
};

class KeyEventListener : EventListener
{
    virtual void onMouseButtonDown(KeyEvent&) = 0;
    virtual void onMouseButtonUp(KeyEvent&) = 0;
    virtual void onMouseMove(KeyEvent&) = 0;
};

class Keyboard : EventSender<KeyEventListener>
{
    public:
        void onKeyDown(int&, int&, int&);
        void onKeyUp(int&, int&, int&);
    private:
        double lastX, lastY;
};

#endif
