#pragma once

#include "Object.h"

#include <glm/mat4x4.hpp>

class Camera : public Object
{
public:
	using super = Object;

	Camera(World* world, Transform transform) 
		: Object(world, transform), m_camera_transform(transform)
	{
		update_matrices(); 
	}

	void init() override;
	void update(float deltatime) override;

	void lerp_transform(float deltatime);

	glm::mat4 get_view_matrix() const { return m_view; };
	glm::mat4 get_projection_matrix() const { return m_projection; };

	void set_transform(Transform new_transform) override;
	void set_location(glm::vec3 new_location) override;
	void set_rotation(Rotator new_rotation) override;
	void add_local_offset(glm::vec3 offset) override;
	void add_rotation_offset(Rotator rotation) override;

	void set_aspect_ratio(float new_ratio) { m_aspect_ratio = new_ratio; update_matrices(); }
	void set_fow_angle(float new_angle) { m_fow_angle = new_angle; update_matrices(); }
	void set_min_clip(float new_min_clip) { m_min_clip = new_min_clip; update_matrices(); }
	void set_max_clip(float new_max_clip) { m_max_clip = new_max_clip; update_matrices(); }

private:
	void update_matrices();

	Transform m_camera_transform;
	glm::mat4 m_view;
	glm::mat4 m_projection;
	float m_aspect_ratio = 1.0f;
	float m_fow_angle = 30.0f;
	float m_min_clip = 0.001f;
	float m_max_clip = 300.0f;
};

