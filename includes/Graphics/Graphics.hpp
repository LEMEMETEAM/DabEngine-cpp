#ifndef BATCH_H_
#define BATCH_H_

#include "Graphics/Graphics.hpp"
#include "Graphics/Batch.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
#include "Core/App.hpp"

class Graphics
{
    public:
        Graphics(App app);
        ~Graphics();

        void begin();
        void end();


    private:
        void updateUniforms();
        void flush();
        void checkFlush();
        
        Batch m_batch;
        Shader* m_currentShader;
        Texture* m_currentTextureSlots[16];
        App m_app;
        float* m_matrix;
};

#endif