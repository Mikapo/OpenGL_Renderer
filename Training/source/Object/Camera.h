#pragma once

#include "Object.h"

#include "glm/mat4x4.hpp"

class Camera : public Object
{
public:
	using super = Object;

	Camera(World* world, Transform transform) 
		: Object(world, transform), camera_transform(transform)
	{
		update_matrices(); 
	}

	void init() override;
	void update(float deltatime) override;

	void lerp_transform(float deltatime);

	glm::mat4 get_view_matrix() const { return view; };
	glm::mat4 get_projection_matrix() const { return projection; };

	void set_transform(Transform new_transform) override;
	void set_location(glm::vec3 new_location) override;
	void set_rotation(Rotator new_rotation) override;
	void add_local_offset(glm::vec3 offset) override;

	void set_aspect_ratio(float new_ratio) { aspect_ratio = new_ratio; update_matrices(); }
	void set_fow_angle(float new_angle) { fow_angle = new_angle; update_matrices(); }
	void set_min_clip(float new_min_clip) { min_clip = new_min_clip; update_matrices(); }
	void set_max_clip(float new_max_clip) { max_clip = new_max_clip; update_matrices(); }

private:
	void update_matrices();

	Transform camera_transform;
	glm::mat4 view;
	glm::mat4 projection;
	float aspect_ratio = 1.0f;
	float fow_angle = 30.0f;
	float min_clip = 0.001f;
	float max_clip = 300.0f;
};

