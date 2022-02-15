#pragma once

#include "Renderer_item.h"

#include "Renderer.h"

class Index_buffer : public Renderer_item
{
public:
    Index_buffer(const void* data, size_t count);
    ~Index_buffer();

    void bind() const;
    void unbind() const;
    inline size_t get_count() const { return m_count; }

private:
    size_t m_count;
};
