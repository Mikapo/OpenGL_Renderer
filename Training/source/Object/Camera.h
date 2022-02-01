#pragma once

#include "Object.h"

#include "glm/mat4x4.hpp"

class Camera : public Object
{
public:
	using super = Object;

	Camera(World* world) : Object(world) { update_matrices(); }

	glm::mat4 get_view_matrix() const { return view; };
	glm::mat4 get_projection_matrix() const { return projection; };

	void set_transform(Transform new_transform) override;
	void set_location(glm::vec3 new_location) override;
	void set_rotation(Rotator new_rotation) override;

private:
	void update_matrices();

	glm::mat4 view;
	glm::mat4 projection;
};

