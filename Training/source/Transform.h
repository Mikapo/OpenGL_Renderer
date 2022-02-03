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

	Rotator operator- (const Rotator& other)
	{
		return Rotator(pitch - other.pitch, yaw - other.yaw, roll - other.roll);
	}
	Rotator operator+ (const Rotator& other)
	{
		return Rotator(pitch + other.pitch, yaw + other.yaw, roll + other.roll);
	}
	Rotator operator* (float value)
	{
		return Rotator(pitch * value, yaw * value, roll * value);
	}

	float difference(const Rotator& other)
	{
		float pitch_difference = pitch - other.pitch;
		if (pitch_difference < 0)
			pitch_difference *= -1;

		float yaw_difference = yaw - other.yaw;
		if (yaw_difference < 0)
			yaw_difference *= -1;

		float roll_difference = roll - other.roll;
		if (roll_difference < 0)
			roll_difference *= -1;

		return pitch_difference + yaw_difference + roll_difference;
	}

};

struct Transform
{
	Transform() = default;
	Transform(glm::vec3 location, Rotator rotation, glm::vec3 scale)
		: location(location), rotation(rotation), scale(scale) {}

	glm::vec3 location = {0.0f, 0.0f, 0.0f};
	Rotator rotation = {0.0f, 0.0f, 0.0f};
	glm::vec3 scale = {1.0f, 1.0f, 1.0f};
};