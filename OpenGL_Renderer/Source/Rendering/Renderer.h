#pragma once

#include <glew.h>

#include "Material.h"
#include "Shader.h"

struct Buffers;
class Renderer
{
public:
    void draw(Buffers* buffers, const class Material* material) const;
    void draw(Buffers* buffers, const class Shader* shader) const;
    void clear() const;
};
