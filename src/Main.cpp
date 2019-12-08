#include "Graphics/Graphics.hpp"
#include "Core/App.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/AppConfig.hpp"
#include "Resources/Shader.hpp"
#include "Utils/Matrix.hpp"
#include "Resources/ResourceManager.hpp"
#include "Cache/LRUCache.hpp"
#include <string>
#include <iostream>
#include <cassert>

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
        g = new Graphics(*app);
        
    }
    void render()
    {
        g->begin();
        g->drawQuad(Vector3f(), Vector3f(10.0f, 10.0f, 0.0f), Vector3f());
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