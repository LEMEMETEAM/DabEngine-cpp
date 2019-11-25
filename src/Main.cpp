#include "Graphics/Batch.hpp"
#include "Core/App.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/AppConfig.hpp"
#include "Resources/Shader.hpp"

class Test : public AppAdapter
{
    public:
    ~Test()
    {
        delete batch;
        delete shader;
    }
    void update(){}
    void init(){
        App::debugLog("INIT");
        batch = new Batch(100);
        const char* v = "#version 330\n\n"
                            "layout (location = 0) in vec3 position;\n"//
                            "layout (location = 1) in vec4 color;\n"//
                            "layout (location = 2) in vec2 uvs;\n"//
                            "layout (location = 3) in vec3 normals;\n\n"//
                            "out vec3 outPosition;\n"//
                            "out vec4 outColor;\n"//
                            "out vec2 outUV;\n"//
                            "out vec3 outNormals;\n\n"//
                            "void main(){\n"//
                            "     gl_Position = vec4(position, 1.0);\n"//
                            "     outPosition = position;\n"//
                            "     outColor = color;\n"//
                            "     outUV = uvs;\n"//
                            "     outNormals = normals;\n"//
                            "}\n";
        const char* f = "#version 330\n\n"
                            "in vec4 outColor;\n"//
                            "out vec4 finalColor;\n\n"//
                            "void main(){\n"//
                            "     finalColor = outColor;\n"//
                            "}\n";
        shader = new Shader(v, f, true);
        shader->load();
    }
    void render()
    {
        batch->begin();
        shader->bind();
        batch->add(data, 12*3);
        shader->unbind();
        batch->flush();
        batch->end();
    }
    void resize(int width, int height){App::debugLog("%d:%d", width, height);}
    
    private:
    Batch* batch;
    float data[12*3] = {
        0,0,0,
        1,1,1,1,
        0,0,
        1,1,1,

        0,-1,0,
        1,1,1,1,
        0,1,
        1,1,1,

        1,-1,0,
        1,1,1,1,
        1,1,
        1,1,1
    };
    Shader* shader;
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