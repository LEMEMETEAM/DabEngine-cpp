#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Graphics/Batch.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
#include "Core/App.hpp"
#include "glm/glm.hpp"
#include "Utils/TextureRegion.hpp"
#include "Utils/Timer.hpp"
#include "Utils/Color.hpp"

class Graphics
{
    public:
        Graphics(App& app);
        ~Graphics();

        void begin();
        void end();

        void setTexture(int unit = 0, Texture* tex = NULL);
        Texture* getTexture(int unit = 0);

        void setShader(Shader* current = NULL);
        Shader* getShader();

<<<<<<< HEAD
        void draw(float* data, const int size, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation);
        void drawQuad(glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, const color<4>& color = 0xFFFFFF, const TextureRegion& region = TextureRegion());
=======
        void draw(float* data, const int size, Vector3f& pos, Vector3f& scale, Vector3f& rotation);
        void drawQuad(Vector3f pos, Vector3f size, Vector3f rotation, const color<4> color = 0xFFFFFF, const TextureRegion region = TextureRegion());
>>>>>>> master

    private:
        void updateUniforms();
        void flush();
        void checkFlush();
        
        Batch m_batch;
        Shader* m_currentShader;
        Texture* m_currentTextureSlots[16];
        App m_app;
        glm::mat4* m_matrix;
};

#endif