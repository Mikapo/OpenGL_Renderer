#include "Renderer.h"

#include "glew.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

void Renderer::draw(const Vertex_array* va, const Index_buffer* ib, const Material* material) const
{
    material->bind();
    va->bind();
    ib->bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)ib->get_count(), GL_UNSIGNED_INT, nullptr);

    material->unbind();
    va->unbind();
    ib->unbind();
}

void Renderer::draw(const Vertex_array* va, const Index_buffer* ib, const Shader* shader) const
{
    shader->bind();
    va->bind();
    ib->bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)ib->get_count(), GL_UNSIGNED_INT, nullptr);

    shader->unbind();
    va->unbind();
    ib->unbind();
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


