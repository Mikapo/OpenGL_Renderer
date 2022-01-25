#pragma once

#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glew.h"

struct point2d
{
    point2d(float x, float y) : x(x), y(y) {}
    float x, y;
};

class Renderer
{
public:
    void draw(const class vertex_array& va, const class index_buffer& ib, const class Shader& shader) const;
    void clear() const;
};
