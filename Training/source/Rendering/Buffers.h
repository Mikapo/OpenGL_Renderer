#pragma once

#include "Renderer.h"
#include <memory>

struct Buffers
{
	Buffers(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, vertex_buffer_layout layout)
		: vb(vertices.data(), sizeof(float) * vertices.size()), 
		  ib(indices.data(), indices.size())
	{
		va.add_buffer(vb, layout);
	}

	vertex_buffer vb;
	vertex_array va;
	index_buffer ib;
};

