#pragma once

#include <vector>

#include "Renderer.h"
#include "Vertex_buffer.h"

struct Vertex_buffer_elements
{
    Vertex_buffer_elements(unsigned int type, int count, unsigned char normalized)
        : m_type(type), m_count(count), m_normalized(normalized)
    {
    }

    unsigned int get_type() const { return m_type; }
    unsigned int get_count() const { return m_count; }
    unsigned char get_normalized() const { return m_normalized; }

    static int get_size_of_type(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;

        case GL_UNSIGNED_INT:
            return 4;

        case GL_BYTE:
            return 1;
        default:
            return -1;
        }
    }

private:
    unsigned int m_type;
    int m_count;
    unsigned char m_normalized;

};

class Vertex_buffer_layout
{
public:
    Vertex_buffer_layout() : m_stride(0) {}

    template <typename T>
    void push(unsigned int count)
    {
        static_assert(false);
    }
    template <>
    void push<float>(unsigned int count)
    {
        m_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
        m_stride += count * Vertex_buffer_elements::get_size_of_type(GL_FLOAT);
    }
    template <>
    void push<unsigned int>(unsigned int count)
    {
        m_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
        m_stride += count * Vertex_buffer_elements::get_size_of_type(GL_UNSIGNED_INT);
    }
    template <>
    void push<unsigned char>(unsigned int count)
    {
        m_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
        m_stride += count * Vertex_buffer_elements::get_size_of_type(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<Vertex_buffer_elements>& get_elements() const { return m_elements; }
    inline unsigned int get_stride() const { return m_stride; }

private:
    std::vector<Vertex_buffer_elements> m_elements;
    int m_stride;
};
