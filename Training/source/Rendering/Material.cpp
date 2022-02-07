#include "Material.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Material::update_shader(glm::mat4 modelview, glm::mat4 projection) const
{
	shader->set_uniform_mat4f("modelview", modelview);
	shader->set_uniform_mat4f("projection", projection);
}

void Material::add_texture(std::shared_ptr<Texture> texture, unsigned int slot)
{
	has_texture = true;
	textures[slot] = texture;
}

void Material::bind() const
{
	shader->set_uniform4f("ambient", ambient.x, ambient.y, ambient.z, ambient.w);
	shader->set_uniform4f("diffuse", diffuse.x, diffuse.y, diffuse.z, diffuse.w);
	shader->set_uniform4f("specular", specular.x, specular.y, specular.z, specular.w);
	shader->set_uniform1f("shininess", shininess);

	for (auto texture : textures)
	{
		texture.second->Bind(texture.first);
	}

	//shader->set_uniform1i("uses_texture", (int)has_texture);
	shader->set_uniform1i("tex", 0);
	shader->bind();
}

void Material::unbind() const
{
	shader->unbind();

	for (auto texture : textures)
	{
		texture.second->UnBind();
	}
}
