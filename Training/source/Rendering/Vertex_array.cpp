
#include "Vertex_array.h"

#include "Vertex_buffer.h"

Vertex_array::Vertex_array()
{
    glGenVertexArrays(1, &m_renderer_id);
}

Vertex_array::~Vertex_array()
{ 
    glDeleteVertexArrays(1, &m_renderer_id); 
}

void Vertex_array::add_buffer(const Vertex_buffer& vb, const Vertex_buffer_layout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.get_stride(), (const void*)offset);
        offset += element.count * Vertex_buffer_elements::get_size_of_type(element.type);
    }
}

void Vertex_array::bind() const { glBindVertexArray(m_renderer_id); }

void Vertex_array::unbind() const { glBindVertexArray(0); }
