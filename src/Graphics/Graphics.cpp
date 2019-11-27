#include "Graphics/Graphics.hpp"
#include <vector>

Graphics::Graphics(App app)
:m_app(app),
m_batch(1024),
m_currentShader(NULL)
{}

Graphics::~Graphics()
{
    delete m_currentShader;
}

void Graphics::updateUniforms()
{
    //add matricies

    for(int i = 0; i < 16; i++)
    {
        m_currentShader->setUniform1i("texture"+i, i);
    }
}

void Graphics::begin()
{
    m_batch.begin();

    //ADD REST LATER
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