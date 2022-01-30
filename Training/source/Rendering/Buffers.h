#pragma once

#include "Renderer.h"
#include <memory>

struct Buffers
{
	Buffers(vertex_buffer* vb, vertex_array* va, index_buffer* ib) 
		: vb(vb), va(va), ib(ib) {}

	std::unique_ptr<vertex_buffer> vb;
	std::unique_ptr<vertex_array> va;
	std::unique_ptr<index_buffer> ib;
};

