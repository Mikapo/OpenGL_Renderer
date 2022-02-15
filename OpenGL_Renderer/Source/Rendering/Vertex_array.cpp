
#include "Vertex_array.h"

#include "Vertex_buffer.h"

Vertex_array::Vertex_array()
{
    glGenVertexArrays(1, &m_id);
}

Vertex_array::~Vertex_array()
{ 
    if(is_valid())
        glDeleteVertexArrays(1, &m_id);
}

void Vertex_array::add_buffer(const Vertex_buffer& vb, const Vertex_buffer_layout& layout) const
{
    bind();
    vb.bind();
    const auto& elements = layout.get_elements();
    unsigned int offset = 0;
    for (GLuint i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);

        glVertexAttribPointer(
            i, element.get_count(), 
            element.get_type(), 
            element.get_normalized(), 
            layout.get_stride(), 
            reinterpret_cast<const void*>(offset));

        offset += element.get_count() * Vertex_buffer_elements::get_size_of_type(element.get_type());
    }
}

void Vertex_array::bind() const 
{ 
    if (is_valid())
        glBindVertexArray(m_id);
}

void Vertex_array::unbind() 
{ 
    glBindVertexArray(0); 
}
