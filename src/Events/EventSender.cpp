#include "Events/EventSender.hpp"
#include "Events/EventListener.hpp"

void EventSender::addListener(EventListener* l)
{
    listeners.push_back(l);
}
