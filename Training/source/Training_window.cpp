#include "Training_window.h"

#include <iostream>
#include "Rendering/Cube_buffers.h"
#include <unordered_map>
#include "Shader_compiler.h"

void Training_window::init()
{
	super::init();

	world.init();



	Transform camera_transform;
	camera_transform.translation = { 0.0f, -2.0f, 0.0f };
	world.spawn_camera(camera_transform);

	Transform cube_transform;
	cube_transform.scale = { 0.25f, 0.25f, 0.25f };
	cube = world.spawn_mesh_object(cube_transform);

	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material material(shader);
	cube->add_mesh(Cube_buffers::get(), material);

	Transform light_transform;
	light_transform.translation = { 0.0f, -3.0f, 0.0f };
	world.spawn_light(light_transform);
}

void Training_window::cleanup() 
{ 
	super::cleanup();  
}

void Training_window::update(float deltatime)
{
	Rotator rotation = cube->get_rotation();
	rotation.yaw -= 0.5f * deltatime;

	glm::vec3 location = cube->get_location();
	location = location + -cube->get_right_vector() * 0.25f * deltatime;
	cube->set_location(location);
	cube->set_rotation(rotation);

	world.render();
}
