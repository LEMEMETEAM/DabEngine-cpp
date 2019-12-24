#ifndef SCENESTACK_H_
#define SCENESTACK_H

#include <vector>

class Scene;

class SceneStack
{
    public:
    void push(Scene* new_scene);
    void pushOverlay(Scene* new_overlay);

    void draw();
    void update();

    private:
    std::vector<Scene*> stack;
};

inline void SceneStack::push(Scene* new_scene)
{
    stack.pop_back();
    stack.push_back(new_scene);
}

inline void SceneStack::pushOverlay(Scene* new_overlay)
{
    stack.push_back(new_overlay);
}

#endif