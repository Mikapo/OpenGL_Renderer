#pragma once

#include <memory>

#include "Vertex_buffer.h"
#include "Vertex_array.h"
#include "Index_buffer.h"


struct Buffers
{
	Buffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Vertex_buffer_layout layout)
		: m_vb(vertices.data(), sizeof(float) * vertices.size()), 
		  m_ib(indices.data(), indices.size())
	{
		m_va.add_buffer(m_vb, layout);
	}

	Vertex_buffer m_vb;
	Vertex_array m_va;
	Index_buffer m_ib;
};

