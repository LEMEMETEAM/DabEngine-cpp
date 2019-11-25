#include "Graphics/Batch.hpp"

Batch::Batch(int size)
:m_buffer(size*6, {
    VertexAttrib(0, "position", 3),
    VertexAttrib(1, "color", 4),
    VertexAttrib(2, "texCoords", 2),
    VertexAttrib(3, "normals", 3)}), 
m_size(size),
m_idx(0),
m_begun(false)
{}

void Batch::begin()
{
    if(m_begun) return;
    m_begun = true;
    m_buffer.bind();
}

void Batch::add(float* data, int length)
{
    for(int i = 0; i < length/12; i++)
    {
        m_buffer.put(*(data + (i*12+0)));
        m_buffer.put(*(data + (i*12+1)));
        m_buffer.put(*(data + (i*12+2)));

        m_buffer.put(*(data + (i*12+3)));
        m_buffer.put(*(data + (i*12+4)));
        m_buffer.put(*(data + (i*12+5)));
        m_buffer.put(*(data + (i*12+6)));

        m_buffer.put(*(data + (i*12+7)));
        m_buffer.put(*(data + (i*12+8)));

        m_buffer.put(*(data + (i*12+9)));
        m_buffer.put(*(data + (i*12+10)));
        m_buffer.put(*(data + (i*12+11)));

        m_idx++;
    }
}

void Batch::end()
{
    if(!m_begun) return;

    m_begun = false;
    m_buffer.unbind();
}

void Batch::flush()
{
    if(m_idx > 0)
    {
        m_buffer.draw(GL_TRIANGLES, 0, m_idx);
        m_buffer.clear();

        m_idx = 0;
    }
}