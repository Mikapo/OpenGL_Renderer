#include "Texture.h"

#include "stb_image/stb_Image.h"


Texture::Texture(const std::string& path) : m_filepath(path) 
{
    stbi_set_flip_vertically_on_load(1);
    m_Local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    glGenTextures(1, &m_rendererID);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Local_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_Local_buffer)
        stbi_image_free(m_Local_buffer);
}

Texture::~Texture() { glDeleteTextures(1, &m_rendererID); }

void Texture::Bind(Texture_slot slot) const
{
    glActiveTexture(GL_TEXTURE0 + (int)slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void Texture::UnBind() { glBindTexture(GL_TEXTURE_2D, 0); }
