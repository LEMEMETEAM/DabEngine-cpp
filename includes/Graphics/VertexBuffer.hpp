#ifndef VERTEXBUFFER_H_
#define VERTEXBUFFER_H_

#include "GL/glew.h"
#include <vector>

struct VertexAttrib
{
	int m_location;
	const char* m_name;
	int m_numComponents;

	VertexAttrib(int location, const char* name, int numComponents)
	:m_location(location), m_name(name), m_numComponents(numComponents){}
};

class VertexBuffer
{
	public:
		VertexBuffer(int size, const std::vector<VertexAttrib>& attribs);
		~VertexBuffer();
		void put(float f);
        void clear();
		void bind();
		void draw(GLenum type, int first, int count);
		void unbind();
	private:
		GLuint m_vbo, m_vao;
		float* m_buffer;
        int m_buffersize;
		int m_vertcount;
		int m_totalComponents;
		int m_bufferpos;
		std::vector<VertexAttrib> m_attribs;
		
};

#endif