#ifndef EVENTSENDER_H_
#define EVENTSENDER_H_

#include <vector>

class EventListener;

template <typename T>
class EventSender
{
    public:
        void addListener(EventListener*);
        void removeListener(EventListener*);
        void removeAll();
    private:
        std::vector<EventListener*> listeners;
};

#endif
