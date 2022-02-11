#pragma once

#include <glew.h>

#include "Index_buffer.h"
#include "Material.h"
#include "Shader.h"
#include "Vertex_array.h"
#include "Vertex_buffer.h"


class Renderer
{
public:
    void draw(const class Vertex_array* va, const class Index_buffer* ib, const class Material* material) const;
    void draw(const class Vertex_array* va, const class Index_buffer* ib, const class Shader* shader) const;
    void clear() const;
};
