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

    glGenBuffers(1, &m_vbo)
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_buffer), m_buffer, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &m_vao);
}

void put(float f)
{
    if(total < sizeof(m_buffer))
    {
        float* p = m_buffer++;
        p = f;
        total++;
    }
}
