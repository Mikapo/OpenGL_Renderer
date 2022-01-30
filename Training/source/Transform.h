#pragma once

#include "glm/vec3.hpp"

struct Rotator
{
	Rotator() = default;
	Rotator(float pitch, float yaw, float roll)
		: pitch(pitch), yaw(yaw), roll(roll) {}

	float pitch = 0;
	float yaw = 0;
	float roll = 0;
};

struct Transform
{
	Transform() = default;
	Transform(glm::vec3 translation, Rotator rotation, glm::vec3 scale) 
		: translation(translation), rotation(rotation), scale(scale) {}

	glm::vec3 translation = {0.0f, 0.0f, 0.0f};
	Rotator rotation = {0.0f, 0.0f, 0.0f};
	glm::vec3 scale = {1.0f, 1.0f, 1.0f};
};