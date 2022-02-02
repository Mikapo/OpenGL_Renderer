#include "Mesh.h"

#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "Object/Mesh_object.h"
#include "World.h"

#include <array>
#include <iostream>


void Mesh::render()
{
	glm::mat4 world_model = calculate_model_matrix(owner->get_transform());
	glm::mat4 relative_model = calculate_model_matrix(relative_transform);
	glm::mat4 model = world_model * relative_model;

	glm::mat4 view = world->get_camera_view_matrix();
	glm::mat4 projection = world->get_camera_projection_matrix();
	glm::mat4 modelview = view * model;

	material.update_shader(modelview, projection);
	renderer.draw(geometry->va.get(), geometry->ib.get(), material.get_shader());
}

glm::mat4 Mesh::calculate_model_matrix(Transform transform)
{
	if (!owner)
		throw(1);

	glm::mat4 identity = glm::mat4(1);

	glm::mat4 pitch = glm::rotate(identity, transform.rotation.pitch, glm::vec3(1, 0, 0));
	glm::mat4 yaw = glm::rotate(identity, transform.rotation.yaw, glm::vec3(0, 0, 1));
	glm::mat4 roll = glm::rotate(identity, transform.rotation.roll, glm::vec3(0, 1, 0));
	glm::mat4 rotation = roll * yaw * pitch;

	glm::mat4 scale = glm::scale(identity, transform.scale);
	glm::mat4 translation = glm::translate(identity, transform.location);
	glm::mat4 model = translation * scale * rotation;

	return model;
}
