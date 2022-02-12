#pragma once

#include "Renderer.h"

class Index_buffer
{
public:
    Index_buffer(const void* data, size_t count);
    ~Index_buffer();

    void bind() const;
    void unbind() const;
    inline size_t get_count() const { return m_count; }

private:
    unsigned int m_renderer_id;
    size_t m_count;
};
