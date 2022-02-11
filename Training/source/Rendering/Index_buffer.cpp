#include "Index_buffer.h"

Index_buffer::Index_buffer(const void* data, size_t count) : m_count(count)
{
    glGenBuffers(1, &m_renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * count, data, GL_STATIC_DRAW);
}

Index_buffer::~Index_buffer() { glDeleteBuffers(1, &m_renderer_id); }

void Index_buffer::bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id); }

void Index_buffer::unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
