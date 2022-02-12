#include "Renderer.h"

#include "glew.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "Buffers.h"

void Renderer::draw(Buffers* buffers, const Material* material) const
{
    material->bind();
    buffers->m_va.bind();
    buffers->m_ib.bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)buffers->m_ib.get_count(), GL_UNSIGNED_INT, nullptr);

    material->unbind();
    buffers->m_va.unbind();
    buffers->m_ib.unbind();
}

void Renderer::draw(Buffers* buffers, const Shader* shader) const
{
    shader->bind();
    buffers->m_va.bind();
    buffers->m_ib.bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)buffers->m_ib.get_count(), GL_UNSIGNED_INT, nullptr);

    shader->unbind();
    buffers->m_va.unbind();
    buffers->m_ib.unbind();
}

void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


