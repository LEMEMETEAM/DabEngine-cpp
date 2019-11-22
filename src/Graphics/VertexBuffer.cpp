#include "Graphics/VertexBuffer.hpp"

static int total = 0;

VertexBuffer::VertexBuffer(int size, std::vector<VertexAttrib> attribs)
:m_vertcount(size), m_attribs(attribs)
{
    for(VertexAttrib a : m_attribs)
    {
        m_totalComponents += a.numComponents;
    }

    m_buffer = new float[m_vertcount * m_totalComponents];
    m_buffersize = m_vertcount * m_totalComponents;

    glGenBuffers(1, &m_vbo)
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_buffer), m_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
}

void VertexBuffer::put(float f)
{
    if(total < m_buffersize)
    {
        m_buffer++ = f;
        total++;
    }
    else
    {
        App::debugLog(HIGH, "Buffer overflow");
    }
}

void VertexBuffer::clear()
{
    memset(m_buffer, 0, sizeof(float) * m_buffersize);
}

void VertexBuffer::bind()
{
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    int offset = 0;

    int stride = totalComponents * sizeof(float);

    for(int i = 0; i < m_attribs.size(); i++)
    {
        VertexAttrib a = m_attribs[i];
        glVertexAttribPointer(a.location, a.numComponents, GL_FLOAT, false, stride, (void*)offset);
        glEnableVertexAttribArray(a.location);
        offset += a.numComponents * sizeof(float);
    }
}

void VertexBuffer::draw(GLenum type, int first, int count)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_buffer);
    glDrawArrays(type, first, count);
}

void VertexBuffer::unbind()
{
    for(int i = 0; i < m_attribs.size(); i++)
    {
        VertexAttrib a = m_attribs[i];
        glDisableVertexAttribArray(a.location);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
