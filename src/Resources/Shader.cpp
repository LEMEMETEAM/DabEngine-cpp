#include "GL/glew.h"
#include "Resources/Shader.hpp"
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <tuple>
#include "Core/App.hpp"

Shader::Shader(std::string vertex, std::string fragment, bool source = false)
:Resource(),
m_vertexShader(vertex),
m_fragmentShader(fragment),
m_program(0),
m_vert(0),
m_frag(0),
m_programBackup(0),
m_source(source)
{}

void Shader::create()
{
    m_ready = compile(m_vertexShader, m_fragmentShader, m_source);
}

bool Shader::compile(std::string v, std::string f, bool s)
{
    m_vert = s ? createShaderFromString(v, GL_VERTEX_SHADER) : createShaderFromFile(v, GL_VERTEX_SHADER);
    m_frag = s ? createShaderFromString(f, GL_FRAGMENT_SHADER) : createShaderFromFile(f, GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    if(!m_program)
    {
        App::debugLog("Program not created\n");
        return false;
    }

    glAttachShader(m_program, m_vert);

    glAttachShader(m_program, m_frag);

    glLinkProgram(m_program);

    glValidateProgram(m_program);

    return true;
}

GLuint Shader::createShaderFromFile(std::string filename, GLuint type)
{
    std::ifstream s;
    s.open(filename);

    std::string line;
    std::string text;
    while(s >> line)
    {
        if(line.find("#include ") != std::string::npos)
        {
            line.erase(line.find("#include "), 9);
            line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());

            std::ifstream include;
            include.open(line);

            std::string _text;
            std::string _line;
            while(include >> line)
            {
                _text += _line;
            }

            include.close();

            line = _text;
        }
        text += line;
    }

    s.close();

    return createShaderFromString(text.c_str(), type);
}

GLuint Shader::createShaderFromString(std::string source, GLuint type)
{
    GLuint shader = glCreateShader(type);

    const char* s = source.c_str();

    App::debugLog("%s\n", source);
    glShaderSource(shader, 1, &s, NULL);
    glCompileShader(shader);

    return shader;
}

void Shader::bind()
{
    int pb;
    glGetIntegerv(GL_CURRENT_PROGRAM, &pb);
    m_programBackup = pb;

    glUseProgram(m_program);
}

void Shader::unbind()
{
    glUseProgram(m_programBackup);
}

void Shader::destroy()
{
    glDeleteShader(m_vert);
    glDeleteShader(m_frag);
    glDeleteProgram(m_program);
}