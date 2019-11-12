#ifndef APPADAPTER_H_
#define APPADAPTER_H_

class App;

class AppAdapter
{
    public:
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void resize(int width, int height) = 0;
        virtual void init() = 0;
        void connectApp(App* app)
        {
            this->app = app;
        }
        App* app;
};
#endif