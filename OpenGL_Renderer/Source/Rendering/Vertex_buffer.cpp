#include "Vertex_buffer.h"

#include "Renderer.h"

Vertex_buffer::Vertex_buffer(const void* data, GLsizeiptr size)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Vertex_buffer::~Vertex_buffer()
{
    if(is_valid())
        glDeleteBuffers(1, &m_id);
}

void Vertex_buffer::bind() const
{
    if(is_valid())
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void Vertex_buffer::unbind()
{ 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
}
