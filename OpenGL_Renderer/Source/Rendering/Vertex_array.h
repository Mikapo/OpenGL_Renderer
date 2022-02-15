#pragma once

#include "Renderer_item.h"

#include "Vertex_buffer_layout.h"

#include <utility>

class Vertex_array : public Renderer_item
{
public:

    Vertex_array();
    ~Vertex_array();

    void add_buffer(const class Vertex_buffer& vb, const Vertex_buffer_layout& layout) const;
    void bind() const;
    static void unbind();
};