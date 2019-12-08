#include "Graphics/Graphics.hpp"
#include <vector>
#include "Utils/dmath.hpp"
#include "Resources/ResourceManager.hpp"

Graphics::Graphics(App app)
:m_app(app),
m_batch(1024),
m_currentShader(NULL),
m_matrix(NULL)
{}

Graphics::~Graphics()
{
    delete m_currentShader;
}

void Graphics::updateUniforms()
{
    m_currentShader->setUniformMatrix4f("m_proj", m_matrix->get());

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
        m_matrix = new Matrix4f(dmath::buildMatrixOrtho(0, m_app.getWindow().getWidth(true), m_app.getWindow().getHeight(true), 0));
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
        if(m_currentTextureSlots[i] != NULL)
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
}

void Graphics::checkFlush()
{
    if(m_batch.getIdx() >= m_batch.getSize())
    {
        flush();
    }
}

void Graphics::setTexture(int unit = 0, Texture* tex)
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

Texture* Graphics::getTexture(int unit = 0)
{
    return  m_currentTextureSlots[unit];
}