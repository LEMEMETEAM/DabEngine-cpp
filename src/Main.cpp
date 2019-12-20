#include "Graphics/Graphics.hpp"
#include "Core/App.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/AppConfig.hpp"
#include <string>
#include <iostream>
#include <cassert>
#include "Resources/ResourceManager.hpp"
#include "Script/ScriptManager.hpp"

class Test : public AppAdapter
{
    public:
    Test(){}
    ~Test()
    {
        delete g;
    }
    void update(){}
    void init(){
        App::debugLog("INIT");
        ResourceManager::init();
        g = new Graphics(app);
        
        ScriptManager::getManager().loadFromFile("test.lua");
    }
    void render()
    {
        g->begin();
        g->drawQuad(glm::vec3{app->getWindow().getWidth()/2, app->getWindow().getHeight()/2, 0}, glm::vec3{600,600,0}, glm::vec3());
        g->end();
    }
    void resize(int width, int height){App::debugLog("%d:%d", width, height);}
    
    private:
    Graphics* g;
};

int main()
{
    AppConfig conf = AppConfig();
    conf.title = "test";
    conf.width = 800;
    conf.height = 600;

    App app(new Test(), conf);
    app.run();

    return 0;
}