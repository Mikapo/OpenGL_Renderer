#include "Renderer.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "glew.h"

void Renderer::draw(const vertex_array& va, const index_buffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


