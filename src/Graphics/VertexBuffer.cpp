#include "Graphics/VertexBuffer.hpp"
#include "Core/App.hpp"

static int total = 0;

VertexBuffer::VertexBuffer(int size, const std::vector<VertexAttrib>& attribs)
:m_vertcount(size), m_attribs(attribs)
{
    for(VertexAttrib a : m_attribs)
    {
        m_totalComponents += a.m_numComponents;
    }

    m_buffersize = m_vertcount * m_totalComponents;
    m_buffer = new float[m_buffersize];

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_buffersize*sizeof(float), m_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
}

VertexBuffer::~VertexBuffer()
{
    delete[] m_buffer;
}

void VertexBuffer::put(float f)
{
    if(m_bufferpos > m_buffersize) return;
	*(m_buffer + m_bufferpos) = f;
    m_bufferpos++;
}

void VertexBuffer::clear()
{
    m_bufferpos = 0;
    delete[] m_buffer;
    m_buffer = new float[m_buffersize];
}

void VertexBuffer::bind()
{
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    int offset = 0;

    int stride = m_totalComponents * sizeof(float);

    for(int i = 0; i < m_attribs.size(); i++)
    {
        VertexAttrib a = m_attribs[i];
        glVertexAttribPointer(a.m_location, a.m_numComponents, GL_FLOAT, GL_FALSE, stride, (void*)offset);
        glEnableVertexAttribArray(a.m_location);
        offset += a.m_numComponents * sizeof(float);
    }
}

void VertexBuffer::draw(GLenum type, int first, int count)
{
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_buffersize*sizeof(float), m_buffer);
    glDrawArrays(type, first, count);
}

void VertexBuffer::unbind()
{
    for(int i = 0; i < m_attribs.size(); i++)
    {
        VertexAttrib a = m_attribs[i];
        glDisableVertexAttribArray(a.m_location);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}
