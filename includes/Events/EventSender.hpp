#ifndef EVENTSENDER_H_
#define EVENTSENDER_H_

#include <vector>

#include "Events/EventListener.hpp"
#include <memory>

template <typename T>
class EventSender
{
    public:
        void pushListener(const T& l);
        void popListener();
        void removeAll();
        virtual ~EventSender() = 0;
    protected:
        std::vector<T> listeners;
};

template <typename T>
EventSender<T>::~EventSender(){}

#endif
