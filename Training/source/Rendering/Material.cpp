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

	update_lighting();
}

void Material::update_lighting()
{
	glm::vec4 light_dir(0.0f, -3.0f, 0.0f, 1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	light_dir = view * light_dir;

	shader->set_uniform4f("light1posn", light_dir.x, light_dir.y, light_dir.z, light_dir.w);
	shader->set_uniform4f("light1color", 1.0f, 0.0f, 0.0f, 1.0f);
}


