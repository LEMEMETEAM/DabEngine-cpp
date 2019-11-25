#include "Graphics/Graphics.hpp"

Graphics::Graphics(App app)
:m_app(app),
m_batch(1024),
m_currentShader(NULL)
{}

Graphics::~Graphics()
{
    delete m_currentShader;
}

void Graphics::begin()
{
    m_batch.begin();

    //ADD REST LATER
}

void Graphics::end()
{
    flush();
    m_batch.end();
}