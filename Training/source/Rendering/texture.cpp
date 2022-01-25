#include "texture.h"

#include "stb_image/stb_Image.h"


texture::texture(const std::string& path) : m_filepath(path) 
{
    stbi_set_flip_vertically_on_load(1);
    m_Local_buffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    glGenTextures(1, &m_rendererID);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);

    glTextureParameteri(GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexSubImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Local_buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (m_Local_buffer)
        stbi_image_free(m_Local_buffer);
}

texture::~texture() { glDeleteTextures(1, &m_rendererID); }

void texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

void texture::UnBind() { glBindTexture(GL_TEXTURE_2D, 0); }
