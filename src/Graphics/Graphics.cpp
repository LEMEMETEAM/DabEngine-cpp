#include "Graphics/Graphics.hpp"
#include <vector>
#include "Resources/ResourceManager.hpp"
#include <cmath>
#include <algorithm>
#include <iterator>
#include <memory>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

Graphics::Graphics(App& app)
:m_app(app),
m_batch(1024),
m_currentShader(NULL),
m_currentTextureSlots{nullptr},
m_matrix(NULL)
{}

Graphics::~Graphics()
{
    delete m_currentShader;
    delete m_matrix;
}

void Graphics::updateUniforms()
{
    m_currentShader->setUniformMatrix4f("m_proj", glm::value_ptr(*m_matrix));

    for(int i = 0; i < 16; i++)
    {
        m_currentShader->setUniform1i("texture"+i, i);
    }
}

void Graphics::begin()
{
    m_batch.begin();

    if(m_matrix == NULL)
    { 
        m_matrix = new glm::mat4(glm::ortho((float)0, (float)m_app.getWindow().getWidth(true), (float)m_app.getWindow().getHeight(true), (float)0));
    }

    m_currentTextureSlots[0] = &ResourceManager::defaultTexture;
    m_currentShader = &ResourceManager::defaultShader;

    m_currentShader->bind();

    updateUniforms();
}

void Graphics::end()
{
    flush();
    m_batch.end();
}

void Graphics::flush()
{
    std::vector<Texture*> bound;
    for(int i = 0; i < 16; i++)
    {
        if(m_currentTextureSlots[i] != nullptr)
        {
            m_currentTextureSlots[i]->bind(i);
            bound.push_back(m_currentTextureSlots[i]);
        }
    }
    m_batch.flush();
    for(Texture* t : bound)
    {
        t->unbind();
    }
    bound.clear();
}

void Graphics::checkFlush()
{
    if(m_batch.getIdx() >= m_batch.getSize())
    {
        flush();
    }
}

void Graphics::setTexture(int unit, Texture* tex)
{
    if(tex != m_currentTextureSlots[unit] && m_batch.hasBegun())
    {
        flush();
        if(unit == 0 && tex == NULL)
        {
            m_currentTextureSlots[unit] = &ResourceManager::defaultTexture;
            return;
        }
        m_currentTextureSlots[unit] = tex;
    }
}

Texture* Graphics::getTexture(int unit)
{
    return  m_currentTextureSlots[unit];
}

void Graphics::setShader(Shader* current)
{
    if(m_currentShader != current && m_batch.hasBegun())
    {
        flush();
        m_currentShader = current == NULL ? &ResourceManager::defaultShader : current;
        m_currentShader->bind();
        updateUniforms();
    }
}

Shader* Graphics::getShader()
{
    return m_currentShader;
}

void Graphics::draw(float* data, const int size, glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation)
{
    checkFlush();

    glm::mat4 final(1.0f);
    glm::scale(final, scale);
    glm::rotate(final, rotation.z, glm::vec3(0,0,1));
    glm::rotate(final, rotation.y, glm::vec3(0,1,0));
    glm::rotate(final, rotation.x, glm::vec3(1,0,0));
    glm::translate(final, pos);
    
    auto d = std::make_unique<float[]>(size);
    memcpy(d.get(), data, sizeof(float)*size);

    for(int i = 0; i < size/12; i++)
    {
        glm::vec3 vs(d[i*12+0], d[i*12+1], d[i*12+2]);
        glm::vec3 verts = final*glm::vec4(vs, 0.0);
        d[i*12+0] = verts.x;
        d[i*12+1] = verts.y;
        d[i*12+2] = verts.z;
    }

    m_batch.add(d.get(), size);
}

void Graphics::drawQuad(glm::vec3 pos, glm::vec3 size, glm::vec3 rotation, const color<4>& color, const TextureRegion& region)
{
    glm::vec3 normals1{0, 0, 1};
    glm::vec3 normals2{0, 0, -1};
    float data[72]{
        -0.5f, -0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_u, region.m_v,
        normals1.x, normals1.y, normals1.z,

        -0.5f, 0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_u, region.m_t,
        normals1.x, normals1.y, normals1.z,

        0.5f, 0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_s, region.m_t,
        normals1.x, normals1.y, normals1.z,

        0.5f, 0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_s, region.m_t,
        normals2.x, normals2.y, normals2.z,

        0.5f, -0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_s, region.m_v,
        normals2.x, normals2.y, normals2.z,

        -0.5f, -0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_u, region.m_v,
        normals2.x, normals2.y, normals2.z
    };

    draw(data, 72, pos, size, rotation);
}
