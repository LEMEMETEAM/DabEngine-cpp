#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

class Event;

class EventListener
{
    virtual void onNotify(Event&) = 0;
};

#endif
