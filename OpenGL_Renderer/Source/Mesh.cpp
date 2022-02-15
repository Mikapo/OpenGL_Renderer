#include "Mesh.h"

#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "Object/Mesh_object.h"
#include "World.h"
#include "Shadow_map.h"

#include <array>
#include <iostream>

void Mesh::render() const
{
	glm::mat4 model = calculate_model_matrix();

	m_material.update_model(model);
	m_renderer.draw(m_geometry.get(), &m_material);
}

void Mesh::render_to_shadow_map(const Shadow_map* shadow_map)
{
	shadow_map->update_model(calculate_model_matrix());
	m_renderer.draw(m_geometry.get(), shadow_map->get_shader().get());
}

glm::mat4 Mesh::calculate_model_matrix() const
{
	glm::mat4 world_model = calculate_model_matrix_from_transform(m_owner->get_transform());
	glm::mat4 relative_model = calculate_model_matrix_from_transform(m_relative_transform);
	return world_model * relative_model;
}

glm::mat4 Mesh::calculate_model_matrix_from_transform(Transform transform)
{
	glm::mat4 identity = glm::mat4(1);

	glm::mat4 pitch = glm::rotate(identity, glm::radians(transform.m_rotation.m_pitch), glm::vec3(1, 0, 0));
	glm::mat4 yaw = glm::rotate(identity, glm::radians(transform.m_rotation.m_yaw), glm::vec3(0, 0, 1));
	glm::mat4 roll = glm::rotate(identity, glm::radians(transform.m_rotation.m_roll), glm::vec3(0, 1, 0));
	glm::mat4 rotation = roll * yaw * pitch;

	glm::mat4 scale = glm::scale(identity, transform.m_scale);
	glm::mat4 translation = glm::translate(identity, transform.m_location);
	glm::mat4 model = translation * scale * rotation;

	return model;
}
