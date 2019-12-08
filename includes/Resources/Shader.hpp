#ifndef SHADER_H_
#define SHADER_H_

#include "GL/glew.h"
#include "Resources/Resource.hpp"
#include <string>
#include <vector>

class Shader : public Resource
{
    public:
        Shader(std::string vertex, std::string fragment, bool source);

        void bind();
        void unbind();

        void create();
        void destroy();

        bool compile(std::string v, std::string f, bool s); 

        inline void setUniform1i(std::string name, int value){
            if(!m_ready) return;
            
            int id = glGetUniformLocation(m_program, name.c_str());
            if(id > 0)
            {
                glUniform1i(id, value);
            }
        }

        inline void setUniform1f(std::string name, float value)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name.c_str());
            if(id > 0)
            {
                glUniform1f(id, value);
            }
        }

        inline void setUniform2f(std::string name, float x, float y)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name.c_str());
            if(id > 0)
            {
                glUniform2f(id, x, y);
            } 
        }

        inline void setUniform3f(std::string name, float x, float y, float z)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name.c_str());
            if(id > 0)
            {
                glUniform3f(id, x, y, z);
            }
        }

        inline void setUniform4f(std::string name, float x, float y, float z, float w)
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name.c_str());
            if(id > 0)
            {
                glUniform4f(id, x, y, z, w);
            }
        }

        inline void setUniformMatrix4f(std::string name, float matrix[16])
        {
            if(!m_ready) return;
            
            GLuint id = glGetUniformLocation(m_program, name.c_str());
            if(id > 0)
            {
                glUniformMatrix4fv(id, 16, true, matrix);
            }
        }

    private: 
        GLuint createShaderFromFile(std::string filename, GLuint type);
        GLuint createShaderFromString(std::string source, GLuint type);
        GLuint m_program;
        GLuint m_vert, m_frag;
        std::string m_vertexShader, m_fragmentShader;
        bool m_source;
        int m_programBackup;
};

#endif