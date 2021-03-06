#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "GL/glew.h"
#include "Resources/Resource.hpp"

class Texture : public Resource
{
    public:
        Texture(std::string filename, bool mipmap, bool hdr);
        Texture(int width, int height, bool mipmap, bool hdr);
        Texture(GLuint id, int width, int height, bool mipmap, bool hdr);
        virtual ~Texture();

        void bind(int unit);
        void unbind();
        inline int getWidth(){return m_width;}
        inline int getHeight(){return m_height;}
        inline GLuint getID(){return m_tid;}

    protected:
        void create();

    private:
        bool loadRaw();
        GLuint m_tid;
        int m_width, m_height, m_numChannels, m_unitBackup;
        bool m_mipmap, m_hdr, m_created;
        void* m_pixels;
};

#endif