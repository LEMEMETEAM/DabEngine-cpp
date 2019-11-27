#include "Graphics/Batch.hpp"
#include "Core/App.hpp"
#include "Core/AppAdapter.hpp"
#include "Core/AppConfig.hpp"
#include "Resources/Shader.hpp"
#include "Utils/Matrix.hpp"

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

        float mat_data[16] = {
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
            1.0f, 2.0f, 3.0f, 4.0f,
            5.0f, 6.0f, 7.0f, 8.0f,
        };
        float mat_data_2[16] = {
            3.0f, 6.0f, 9.0f, 12.0f,
            3.0f, 6.0f, 9.0f, 12.0f,
            3.0f, 6.0f, 9.0f, 12.0f,
            3.0f, 6.0f, 9.0f, 12.0f
        };
        Matrix4f mat(mat_data);
        Matrix4f mat2(mat_data_2);

        auto mat3 = mat2*mat2;
        App::debugLog("%f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f",
        mat3.get()[0], mat3.get()[1], mat3.get()[2], mat3.get()[3],
        mat3.get()[4], mat3.get()[5], mat3.get()[6], mat3.get()[7],
        mat3.get()[8], mat3.get()[9], mat3.get()[10], mat3.get()[11],
        mat3.get()[12], mat3.get()[13], mat3.get()[14], mat3.get()[15]);
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