#pragma once

#include "Object.h"
#include "glm/vec4.hpp"

class Light : public Object
{
public:

	using super = Object;

	Light(World* world) : Object(world) {}

	void set_transform(Transform new_transform) override;
	void set_location(glm::vec3 new_location) override;
	void set_rotation(Rotator new_rotation) override;

	glm::vec4 get_color() const { return color; }
private:
	glm::vec4 color = { 0.6f, 0.5f, 0.5f, 1.0f };
};

