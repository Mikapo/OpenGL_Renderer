#pragma once

#include "Renderer_item.h"

#include <glew.h>
#include <utility>

class Vertex_buffer : public Renderer_item
{
public:
    Vertex_buffer(const void* data, GLsizeiptr size);
    ~Vertex_buffer();

    void bind() const;
    static void unbind();

};
