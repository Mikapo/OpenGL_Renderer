#include "Material.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

void Material::update_shader(Transform object_transform)
{
	shader->set_uniform4f("ambient", 0.2f, 0.0f, 0.0f, 1.0f);
	shader->set_uniform4f("diffuse", 0.5f, 0.5f, 0.5f, 1.0f);
	shader->set_uniform4f("specular", 5.0f, 5.0f, 5.0f, 1.0f);
	shader->set_uniform1f("shininess", 100.f);

	glm::mat4 modelview = calculate_model_view_matrix(object_transform);
	update_transform(modelview);
	update_lighting();
}

void Material::update_transform(glm::mat4 modelview)
{
	glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.f, 1.0f, 100.0f);
	shader->set_uniform_mat4f("modelview", modelview);
	shader->set_uniform_mat4f("projection", projection);
}

void Material::update_lighting()
{
	glm::vec4 light_dir(0.0f, -3.0f, 0.0f, 1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	light_dir = view * light_dir;

	shader->set_uniform4f("light1posn", light_dir.x, light_dir.y, light_dir.z, light_dir.w);
	shader->set_uniform4f("light1color", 1.0f, 0.0f, 0.0f, 1.0f);
}

glm::mat4 Material::calculate_model_view_matrix(Transform object_transfrom)
{
	glm::mat4 model = glm::mat4(1);
	model *= glm::translate(model, object_transfrom.translation);
	model *= glm::rotate(model, object_transfrom.rotation.pitch, glm::vec3(1, 0, 0));
	model *= glm::rotate(model, object_transfrom.rotation.yaw, glm::vec3(0, 0, 1));
	model *= glm::rotate(model, object_transfrom.rotation.roll, glm::vec3(0, 1, 0));
	model *= glm::scale(model, object_transfrom.scale);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, -2.0f, 0.0f), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

	return view * model;
}
