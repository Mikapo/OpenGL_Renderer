#pragma once

#include <Rendering/Renderer.h>
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"

struct Rotator
{
	Rotator() = default;
	Rotator(float pitch, float yaw, float roll) 
		: pitch(pitch), yaw(yaw), roll(roll) {}

	float pitch = 0, yaw = 0, roll = 0;
};

class Cube
{
public:
	~Cube();

	void init();
	void render();
	void set_rotation(Rotator new_rotation);
	void set_location(glm::vec3 new_location);
	void set_scale(glm::vec3 new_rotation);
	glm::vec3 get_location() { return location; }
	Rotator get_rotation() { return rotation; }
	glm::vec3 get_scale() { return scale; }

private:
	void init_shader();
	void init_buffers();
	void update_transform();
	glm::mat4 calculate_mvp();

	bool has_been_initialized = false;
	Renderer renderer;
	vertex_buffer* vb = nullptr;
	index_buffer* ib = nullptr;
	vertex_array* va = nullptr;
	Shader* shader = nullptr;

	glm::vec3 location = {0, 0, 0};
	Rotator rotation;
	glm::vec3 scale = {1, 1, 1};
};

