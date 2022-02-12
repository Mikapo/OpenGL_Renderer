#pragma once

#include <glew.h>

class Vertex_buffer
{
public:
    Vertex_buffer(const void* data, size_t size);
    ~Vertex_buffer() { glDeleteBuffers(1, &m_renderer_id); }

    void bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id); };
    void unbind() const;

private:
    unsigned int m_renderer_id;
};
