#pragma once

#include "Renderer_item.h"

#include <utility>

#include "Renderer.h"
#include "Texture_slots.h"

class Texture : public Renderer_item
{
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(Texture_slot slot = Texture_slot::texture) const;
    static void unbind();

    inline int GetWidth() const { return m_width; }

private:
    std::string m_filepath;
    unsigned char* m_Local_buffer = nullptr;
    int m_width = 0, m_height = 0, m_bpp = 0;
};
