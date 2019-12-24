#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "Events/Event.hpp"
#include "Events/EventListener.hpp"
#include "Events/EventSender.hpp"

class KeyEvent
{
    public:
        KeyEvent(int key, int scancode, int action, int mod);
        ~KeyEvent(){}
        int getKey(){return key;}
        int getScancode(){return scancode;}
        int getAction(){return action;}
        int getMod(){return mod;}
    private:
        int key, scancode, action, mod;
};

class KeyEventListener : EventListener
{
    public:
    virtual void onKeyDown(KeyEvent&) = 0;
    virtual void onKeyUp(KeyEvent&) = 0;
};

class Keyboard : EventSender<KeyEventListener>
{
    public:
        ~Keyboard(){}
        void onKeyDown(int key, int scancode, int mod);
        void onKeyUp(int key, int scancode, int mod);
    private:
        double lastX, lastY;
};

#endif
