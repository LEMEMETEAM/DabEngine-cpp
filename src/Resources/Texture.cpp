#include "GL/glew.h"
#include "Resources/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "STB/stb_image.h"

Texture::Texture(std::string filename, bool mipmap = false, bool hdr = false)
:Resource(filename), 
m_tid(0), 
m_width(1), 
m_height(1), 
m_numChannels(4), 
m_mipmap(mipmap),
m_hdr(hdr),
m_created(false)
{}

Texture::Texture(int width, int height, bool mipmap = false, bool hdr = false)
:Resource(),
m_tid(0),
m_width(width),
m_height(height),
m_numChannels(4),
m_mipmap(mipmap),
m_hdr(hdr),
m_created(true)
{
    if(hdr) m_pixels = new float[m_numChannels*m_width*m_height];
    else m_pixels = new unsigned char[m_numChannels*m_width*m_height];
    for(int i = 0; i < m_width*m_height; i++)
    {
        if(hdr)
        {
            *(static_cast<float*>(m_pixels + (i*4) + 0)) = (unsigned char)255;
            *(static_cast<float*>(m_pixels + (i*4) + 1)) = (unsigned char)255;
            *(static_cast<float*>(m_pixels + (i*4) + 2)) = (unsigned char)255;
            *(static_cast<float*>(m_pixels + (i*4) + 3)) = (unsigned char)255;
        }
        else
        {
            *(static_cast<unsigned char*>(m_pixels + (i*4) + 0)) = 255;
            *(static_cast<unsigned char*>(m_pixels + (i*4) + 1)) = 255;
            *(static_cast<unsigned char*>(m_pixels + (i*4) + 2)) = 255;
            *(static_cast<unsigned char*>(m_pixels + (i*4) + 3)) = 255;
        }
    }
}

Texture::Texture(GLuint id, int width, int height, bool mipmap = false, bool hdr = false)
:Resource(),
m_tid(id),
m_width(width),
m_height(height),
m_numChannels(4),
m_mipmap(mipmap),
m_hdr(hdr),
m_created(true)
{
    m_ready = true;
}

void Texture::create()
{
    if(m_tid != 0 || m_ready) return;

    if(!m_created) m_ready = loadRaw();

    glGenTextures(1, &m_tid);
    glBindTexture(GL_TEXTURE_2D, m_tid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_mipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if(m_hdr)
        glTexImage2D(GL_TEXTURE_2D, 0, m_numChannels == 4 ? GL_RGBA16F : (m_numChannels == 3 ? GL_RGB16F : (m_numChannels == 1 ? GL_LUMINANCE16 : GL_RGBA16F)), m_width, m_height, 0, m_numChannels == 4 ? GL_RGBA16F : (m_numChannels == 3 ? GL_RGB16F : (m_numChannels == 1 ? GL_LUMINANCE : GL_RGBA16F)), GL_FLOAT, m_pixels);
    else
        glTexImage2D(GL_TEXTURE_2D, 0, m_numChannels == 4 ? GL_RGBA : (m_numChannels == 3 ? GL_RGB : (m_numChannels == 1 ? GL_LUMINANCE : GL_RGBA)), m_width, m_height, 0, m_numChannels == 4 ? GL_RGBA : (m_numChannels == 3 ? GL_RGB : (m_numChannels == 1 ? GL_LUMINANCE : GL_RGBA)), GL_UNSIGNED_BYTE, m_pixels);
    
    if(m_mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    if(m_created) m_ready = true;
}

bool Texture::loadRaw()
{
    if(m_filename.empty())
    {
        int x, y, channels;
        if(m_hdr)
            m_pixels = stbi_loadf(m_filename.c_str(), &x, &y, &channels, 0);
        else
            m_pixels = stbi_load(m_filename.c_str(), &x, &y, &channels, 0);

        if(m_pixels == NULL) return false;

        m_width = x;
        m_height = y;
        m_numChannels = channels;
    }

    return true;
}

Texture::~Texture()
{
    if(m_tid != 0)
    {
        glDeleteTextures(1, &m_tid);
        m_tid = 0;
    }

    delete[] m_pixels;
}

void Texture::bind(int unit = 0)
{
    if(!m_ready) return;

    m_unitBackup = unit;

    glActiveTexture(GL_TEXTURE0 + unit);

    glBindTexture(GL_TEXTURE_2D, m_tid);
}

void Texture::unbind()
{
    if(!m_ready) return;

    glActiveTexture(GL_TEXTURE0 + m_unitBackup);

    glBindTexture(GL_TEXTURE_2D, 0);

    if(m_unitBackup != 0)
    {
        glActiveTexture(GL_TEXTURE0);
    }
}