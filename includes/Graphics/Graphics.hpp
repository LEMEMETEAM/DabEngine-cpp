#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Graphics/Batch.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
#include "Core/App.hpp"
#include "Utils/Matrix.hpp"
#include "Utils/Vector.hpp"
#include "Utils/TextureRegion.hpp"
#include "Utils/Timer.hpp"
#include "Utils/Color.hpp"

class Graphics
{
    public:
        Graphics(App app);
        ~Graphics();

        void begin();
        void end();

        void setTexture(int, Texture*);
        Texture* getTexture(int);

        void setShader(Shader*);
        Shader* getShader();

        void draw(float*, const int, Vector3f, Vector3f, Vector3f);
        void drawQuad(Vector3f, Vector3f, Vector3f, color&, TextureRegion&);

    private:
        void updateUniforms();
        void flush();
        void checkFlush();
        
        Batch m_batch;
        Shader* m_currentShader;
        Texture* m_currentTextureSlots[16];
        App m_app;
        Matrix4f* m_matrix;
};

#endif