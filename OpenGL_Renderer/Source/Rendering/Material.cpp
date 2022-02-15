#include "Material.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Utility/Uniform_names.h"

void Material::update_model(glm::mat4 model) const
{
	m_shader->set_uniform_mat4f(MODEL_UNIFORM_NAME, model);
}

void Material::add_texture(std::shared_ptr<Texture> texture, Texture_slot slot)
{
	m_has_texture = true;
	m_textures[slot] = texture;
}

void Material::bind() const
{
	m_shader->set_uniform4f(AMBIENT_UNIFORM_NAME, m_ambient.x, m_ambient.y, m_ambient.z, m_ambient.w);
	m_shader->set_uniform4f(DIFFUSE_UNIFORM_NAME, m_diffuse.x, m_diffuse.y, m_diffuse.z, m_diffuse.w);
	m_shader->set_uniform4f(SPECULAR_UNIFORM_NAME, m_specular.x, m_specular.y, m_specular.z, m_specular.w);
	m_shader->set_uniform1f(SHININESS_UNIFORM_NAME, m_shininess);

	for (auto texture : m_textures)
	{
		texture.second->bind(texture.first);
	}

	//shader->set_uniform1i("uses_texture", (int)has_texture);
	m_shader->set_uniform1i(TEXTURE_UNIFORM_NAME, (int)Texture_slot::texture);
	m_shader->set_uniform1i(SHAODW_MAP_UNIFORM_NAME, (int)Texture_slot::shadow_map);
	m_shader->bind();
}

void Material::unbind() const
{
	m_shader->unbind();

	for (auto texture : m_textures)
	{
		texture.second->unbind();
	}
}
