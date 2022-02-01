#include "Material.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Material::update_shader(glm::mat4 modelview, glm::mat4 projection)
{
	shader->set_uniform4f("ambient", 0.2f, 0.0f, 0.0f, 1.0f);
	shader->set_uniform4f("diffuse", 0.5f, 0.5f, 0.5f, 1.0f);
	shader->set_uniform4f("specular", 5.0f, 5.0f, 5.0f, 1.0f);
	shader->set_uniform1f("shininess", 100.f);

	shader->set_uniform_mat4f("modelview", modelview);
	shader->set_uniform_mat4f("projection", projection);
}



