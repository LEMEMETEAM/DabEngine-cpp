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

        inline void setUniform1i(const char* name, int value){
            if(!m_ready) return;
            
            int id = glGetUniformLocation(m_program, name);
            if(id > 0)
            {
                glUniform1i(id, value);
            }
        }

        inline void setUniform1f(const char* name, float value)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name);
            if(id > 0)
            {
                glUniform1f(id, value);
            }
        }

        inline void setUniform2f(const char* name, float x, float y)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name);
            if(id > 0)
            {
                glUniform2f(id, x, y);
            } 
        }

        inline void setUniform3f(const char* name, float x, float y, float z)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name);
            if(id > 0)
            {
                glUniform3f(id, x, y, z);
            }
        }

        inline void setUniform4f(const char* name, float x, float y, float z, float w)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name);
            if(id > 0)
            {
                glUniform4f(id, x, y, z, w);
            }
        }

        inline void setUniformMatrix4f(const char* name, float matrix[16])
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name);
            if(id > 0)
            {
                glUniformMatrix4fv(id, 16, true, matrix);
            }
        }

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