#include "Scene/SceneStack.hpp"

#include "Scene/Scene.hpp"

inline void SceneStack::draw()
{
    for(Scene* s : stack)
    {
        s->draw();
    }
}

inline void SceneStack::update()
{
    for(Scene* s : stack)
    {
        s->update();
    }
}