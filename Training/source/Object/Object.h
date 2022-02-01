#pragma once

#include "Transform.h"
#include <vector>
#include <memory>

class World;
class Object
{
public:
	Object(World* owner) : world(owner) {}

	Transform get_transform() const { return transform; }
	virtual void set_transform(Transform new_transform) { update_directional_vectors();  transform = new_transform; }
	glm::vec3 get_location() const { return transform.translation; }
	virtual void set_location(glm::vec3 new_location) { transform.translation = new_location; }
	Rotator get_rotation() const { return transform.rotation; }
	virtual void set_rotation(Rotator new_rotation) { update_directional_vectors();  transform.rotation = new_rotation; }
	glm::vec3 get_scale() const { return transform.scale; }
	virtual void set_scale(glm::vec3 new_scale) { transform.scale = new_scale; }

	glm::vec3 get_forward_vector() const { return forward_vector; }
	glm::vec3 get_up_vector() const { return up_vector; }
	glm::vec3 get_right_vector() const { return right_vector; }

	World* get_world() const { return world; }

private:
	void update_directional_vectors();

	Transform transform;

	World* world;
	glm::vec3 forward_vector = { 0.0f, 1.0f, 0.f };
	glm::vec3 up_vector = { 0.0f, 0.0f, 1.0f };;
	glm::vec3 right_vector = { 1.0f, 0.0f, 0.0f };;
};

