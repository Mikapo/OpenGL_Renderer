#include "Material.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Material::update_shader(glm::mat4 modelview, glm::mat4 projection) const
{
	shader->set_uniform4f("ambient", ambient.x, ambient.y, ambient.z, ambient.w);
	shader->set_uniform4f("diffuse", diffuse.x, diffuse.y, diffuse.z, diffuse.w);
	shader->set_uniform4f("specular", specular.x, specular.y, specular.z, specular.w);
	shader->set_uniform1f("shininess", shininess);

	shader->set_uniform_mat4f("modelview", modelview);
	shader->set_uniform_mat4f("projection", projection);
}



