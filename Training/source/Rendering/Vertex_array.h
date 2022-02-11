#pragma once

#include "Vertex_buffer_layout.h"

class Vertex_array
{
public:

	Vertex_array();
    ~Vertex_array();

	void add_buffer(const class Vertex_buffer& vb, const Vertex_buffer_layout& layout);
    void bind() const;
    void unbind() const;

	private:

		unsigned int m_renderer_id;
};