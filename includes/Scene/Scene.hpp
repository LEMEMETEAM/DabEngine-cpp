#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

class AppAdapter;

class Scene
{
    public:
    Scene(AppAdapter* a);
    virtual ~Scene();

    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void init() = 0;

    virtual void onEnter();
    virtual void onExit();

    protected:
    AppAdapter* m_adapter = nullptr;
};

#endif