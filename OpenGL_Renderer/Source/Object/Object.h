#pragma once

#include <glm/ext/matrix_transform.hpp>
#include <memory>
#include <vector>

#include "Transform.h"

class World;
class Object
{
public:
	Object(World* owner, Transform transform = Transform()) 
		: m_transform(transform), m_world(owner) {}

	virtual void init() {}
	virtual void update(float deltatime) {}

	Transform get_transform() const { return m_transform; }
	virtual void set_transform(Transform new_transform) { m_transform = new_transform;  update_directional_vectors(); }
	glm::vec3 get_location() const { return m_transform.m_location; }
	virtual void set_location(glm::vec3 new_location) { m_transform.m_location = new_location; }
	Rotator get_rotation() const { return m_transform.m_rotation; }
	virtual void set_rotation(Rotator new_rotation) { m_transform.m_rotation = new_rotation; update_directional_vectors(); }
	glm::vec3 get_scale() const { return m_transform.m_scale; }
	virtual void set_scale(glm::vec3 new_scale) { m_transform.m_scale = new_scale; }
	virtual void add_local_offset(glm::vec3 offset);
	virtual void add_rotation_offset(Rotator rotation) { update_directional_vectors(); m_transform.m_rotation = m_transform.m_rotation + rotation; }

	glm::vec3 get_forward_vector() const { return m_forward_vector; }
	glm::vec3 get_up_vector() const { return m_up_vector; }
	glm::vec3 get_right_vector() const { return m_right_vector; }

	World* get_world() const { return m_world; }
	glm::mat4 calulate_rotation_matrix(Rotator rotator);

protected:

private:
	void update_directional_vectors();

	Transform m_transform;

	World* m_world;
	glm::vec3 m_forward_vector = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_up_vector = { 0.0f, 0.0f, 1.0f };;
	glm::vec3 m_right_vector = { 1.0f, 0.0f, 0.0f };;
};

