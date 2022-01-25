#pragma once

#include "Renderer.h"

class texture
{
public:
    texture(const std::string& path);
    ~texture();

    void Bind(unsigned int slot = 0) const;
    void UnBind();

    inline int GetWidth() const { return m_width; }
    inline int GetHeight() const { return m_height; }

private:
    unsigned int m_rendererID = 0;
    std::string m_filepath;
    unsigned char* m_Local_buffer = nullptr;
    int m_width = 0, m_height = 0, m_bpp = 0;
};
