#pragma once

#include <glm/vec3.hpp>

struct Rotator
{
	Rotator() = default;
	Rotator(float pitch, float yaw, float roll)
		: m_pitch(pitch), m_yaw(yaw), m_roll(roll) {}

	float m_pitch = 0;
	float m_yaw = 0;
	float m_roll = 0;

	Rotator operator- (const Rotator& other)
	{
		return Rotator(m_pitch - other.m_pitch, m_yaw - other.m_yaw, m_roll - other.m_roll);
	}
	Rotator operator+ (const Rotator& other)
	{
		return Rotator(m_pitch + other.m_pitch, m_yaw + other.m_yaw, m_roll + other.m_roll);
	}
	Rotator operator* (float value)
	{
		return Rotator(m_pitch * value, m_yaw * value, m_roll * value);
	}

	float difference(const Rotator& other)
	{
		float pitch_difference = m_pitch - other.m_pitch;
		if (pitch_difference < 0)
			pitch_difference *= -1;

		float yaw_difference = m_yaw - other.m_yaw;
		if (yaw_difference < 0)
			yaw_difference *= -1;

		float roll_difference = m_roll - other.m_roll;
		if (roll_difference < 0)
			roll_difference *= -1;

		return pitch_difference + yaw_difference + roll_difference;
	}

};

struct Transform
{
	Transform() = default;
	Transform(glm::vec3 location, Rotator rotation, glm::vec3 scale)
		: m_location(location), m_rotation(rotation), m_scale(scale) {}

	glm::vec3 m_location = {0.0f, 0.0f, 0.0f};
	Rotator m_rotation = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};
};