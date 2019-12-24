#include "Events/EventSender.hpp"
#include "Events/EventListener.hpp"
#include <algorithm>

template <typename T>
void EventSender<T>::pushListener(const T& l)
{
    listeners.push_back(l);
}

template <typename T>
void EventSender<T>::popListener()
{
    listeners.pop_back();
}

template <typename T>
void EventSender<T>::removeAll()
{
    listeners.clear();
}
