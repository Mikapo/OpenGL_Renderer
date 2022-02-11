#include "Vertex_buffer.h"

#include "Renderer.h"

Vertex_buffer::Vertex_buffer(const void* data, size_t size)
{
    glGenBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Vertex_buffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
