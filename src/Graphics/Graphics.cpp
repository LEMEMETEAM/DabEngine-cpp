#include "Graphics/Graphics.hpp"
#include <vector>
#include "Utils/dmath.hpp"
#include "Resources/ResourceManager.hpp"
#include <cmath>
#include <algorithm>
#include <iterator>
#include <memory>
#include "Utils/Color.hpp"

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

void Graphics::setTexture(int unit = 0, Texture* tex = NULL)
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

void Graphics::draw(float* data, const int size, Vector3f& pos, Vector3f& scale, Vector3f& rotation)
{
    checkFlush();

    float s[16] = 
    {
    scale.x(),   0,  0,  0,
    0,   scale.y(),  0,  0,
    0,   0,  scale.z(),  0,
    0,   0,   0,     1
    };

    float t[16] =
    {
    0,0,0,pos.x(),
    0,0,0,pos.y(),
    0,0,0,pos.z(),
    0,0,0,1
    };

    float rz[16] = 
    {
        cos(rotation.z()),-(sin(rotation.z())), 0,
        sin(rotation.z()),cos(rotation.z()), 0,
        0,0,1
    };

    float ry[16] =
    {
        cos(rotation.y()),0,sin(rotation.y()),
        0,1,0,
        -(sin(rotation.y())),0,cos(rotation.y())
    };

    float rx[16] = 
    {
        1,0,0,
        0,cos(rotation.x()),-(sin(rotation.x())),
        0,sin(rotation.x()),cos(rotation.x())
    };

    Matrix4f Rx(rx);
    Matrix4f Ry(ry);
    Matrix4f Rz(rz);

    Matrix4f rot = Rz*Ry*Rx;
    Matrix4f scaleMat(s);
    Matrix4f trans(t);

    Matrix4f final = scaleMat * rot * trans;
    
    auto d = std::make_unique<float[]>(size);
    memcpy(d.get(), data, sizeof(float)*size);

    for(int i = 0; i < size/12; i++)
    {
        Vector3f vs(d[i*12+0], d[i*12+1], d[i*12+2]);
        Vector3f verts = final*vs;
        d[i*12+0] = verts.x();
        d[i*12+1] = verts.y();
        d[i*12+2] = verts.z();
    }

    m_batch.add(d.get(), size);
}

void Graphics::drawQuad(Vector3f pos, Vector3f size, Vector3f rotation, const color<4> color, const TextureRegion region)
{
    Vector3f normals1(0, 0, 1);
    Vector3f normals2(0, 0, -1);
    float data[72]{
        -0.5f, -0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_u, region.m_v,
        normals1.x(), normals1.y(), normals1.z(),

        -0.5f, 0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_u, region.m_t,
        normals1.x(), normals1.y(), normals1.z(),

        0.5f, 0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_s, region.m_t,
        normals1.x(), normals1.y(), normals1.z(),

        0.5f, 0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_s, region.m_t,
        normals2.x(), normals2.y(), normals2.z(),

        0.5f, -0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_s, region.m_v,
        normals2.x(), normals2.y(), normals2.z(),

        -0.5f, -0.5f, 0,
        color.c[0], color.c[1], color.c[2], color.c[3],
        region.m_u, region.m_v,
        normals2.x(), normals2.y(), normals2.z()
    };

    draw(data, 72, pos, size, rotation);
}