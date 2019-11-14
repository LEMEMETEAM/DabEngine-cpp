#include "Events/EventSender.hpp"
#include "Events/EventListener.hpp"
#include <algorithm>

template <typename T>
void EventSender<T>::addListener(T* l)
{
    listeners.push_back(l);
}

template <typename T>
void EventSender<T>::removeListener(T* l)
{
    listeners.erase(std::remove(listeners.begin(), listeners.end(), l), listeners.end());
}

template <typename T>
void EventSender<T>::removeAll()
{
    listeners.clear();
}
