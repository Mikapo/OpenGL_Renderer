#pragma once

#include "Object.h"

#include <glm/vec4.hpp>

class Light : public Object
{
public:

	using super = Object;

	Light(World* world) : Object(world) {}

	glm::vec4 get_color() const { return m_color; }
	void set_color(glm::vec4 new_color) { m_color = new_color; }

	float get_ambient_intensity() const { return m_ambinent_intensity; }

private:
	glm::vec4 m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
	float m_ambinent_intensity = 1.0f;
};

