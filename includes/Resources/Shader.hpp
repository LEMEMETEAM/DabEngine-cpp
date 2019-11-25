#ifndef SHADER_H_
#define SHADER_H_

#include "GL/glew.h"
#include "Resources/Resource.hpp"
#include <string>
#include <vector>

class Shader : public Resource
{
    public:
        Shader(const char* vertex, const char* fragment, bool source);

        void bind();
        void unbind();

        void create();
        void destroy();

        bool compile(const char* v, const char* f, bool s); 

        inline void setUniform(const char* name, int value){glUniform1i()}
    private: 
        GLuint createShaderFromFile(const char* filename, GLuint type);
        GLuint createShaderFromString(const char* source, GLuint type);
        GLuint m_program;
        GLuint m_vert, m_frag;
        const char *m_vertexShader, *m_fragmentShader;
        bool m_source;
        int m_programBackup;
};

#endif