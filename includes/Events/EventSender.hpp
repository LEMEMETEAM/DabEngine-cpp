#ifndef EVENTSENDER_H_
#define EVENTSENDER_H_

#include <vector>

class EventListener;

template <typename T>
class EventSender
{
    public:
        void addListener(T*);
        void removeListener(T*);
        void removeAll();
        virtual ~EventSender() = 0;
    private:
        std::vector<T*> listeners;
};

#endif
