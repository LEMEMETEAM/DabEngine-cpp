#ifndef EVENTLISTENER_H_
#define EVENTLISTENER_H_

#include "Events/Event.hpp"

class EventListener
{
    virtual void onNotify(Event&) = 0;
};

#endif
