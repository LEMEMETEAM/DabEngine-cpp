#include "Core/App.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/AppConfig.hpp"

class Test : public AppAdapter
{
    void update(){}
    void init(){App::debugLog("INIT");}
    void render(){}
    void resize(int width, int height){App::debugLog("%d:%d", width, height);}
};

int main()
{
    AppConfig conf = AppConfig();
    conf.title = "test";
    conf.width = 800;
    conf.height = 600;

    App app(new Test(), &conf);
    app.run();

    return 0;
}