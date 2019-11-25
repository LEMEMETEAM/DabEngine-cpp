#ifndef EVENTSENDER_H_
#define EVENTSENDER_H_

#include <vector>

#include "Events/EventListener.hpp"

template <typename T>
class EventSender
{
    public:
        void addListener(T*);
        void removeListener(T*);
        void removeAll();
        virtual ~EventSender() = 0;
    protected:
        std::vector<T*> listeners;
};

#endif
