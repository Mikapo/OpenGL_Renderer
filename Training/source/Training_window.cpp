#include "Training_window.h"

#include <iostream>
#include "Rendering/Cube_buffers.h"
#include <unordered_map>
#include "Shader_compiler.h"
#include "GLFW/glfw3.h"

void Training_window::init()
{
	super::init();

	world.init();
	init_objects();
	setup_inputs();
}

void Training_window::setup_inputs()
{
	auto mapping = input_handler.add_axis_mapping("move_camera_left", this, &Training_window::move_camera_right);
	mapping->add_key(GLFW_KEY_A, -1);
	mapping->add_key(GLFW_KEY_D, 1);

	mapping = input_handler.add_axis_mapping("move_camera_right", this, &Training_window::move_camera_forward);
	mapping->add_key(GLFW_KEY_S, -1);
	mapping->add_key(GLFW_KEY_W, 1);

	mapping = input_handler.add_axis_mapping("rotate_camera", this, &Training_window::rotate_camera);
	mapping->add_key(GLFW_KEY_Q, 1);
	mapping->add_key(GLFW_KEY_E, -1);
}

void Training_window::cleanup() 
{ 
	super::cleanup();  
}

void Training_window::update(float deltatime)
{
	static float x = 0;
	x += 5.0f * deltatime;
	float offset = 0.1 * glm::sin(0.5 * x);
	glm::vec3 location = second_cube->get_location();
	location.z = offset;
	second_cube->set_location(location);

	cube->add_rotation_offset(Rotator(0.0f, 1.0f, 0.0f) * deltatime);

	world.update(deltatime);
}

void Training_window::render() const
{
	world.render();
}

void Training_window::move_camera_right(float value)
{
	if (value == 0)
		return;

	world.add_current_camera_local_offset(glm::vec3(1.0f, 0.0f, 0.0f) * value * get_delta_seconds());
}

void Training_window::move_camera_forward(float value)
{
	if (value == 0)
		return;

	world.add_current_camera_local_offset(glm::vec3(0.0f, 1.0f, 0.0f) * value * get_delta_seconds());
}

void Training_window::rotate_camera(float value)
{
	if (value == 0)
		return;

	Rotator rotation;
	rotation.yaw = 1.0f * value * get_delta_seconds();
	world.add_current_camera_rotation_offset(rotation);
}

void Training_window::on_window_resize(GLFWwindow* window, int new_width, int new_height)
{
	get_world()->update_aspect_ratio((float)new_width / (float)new_height);
}

void Training_window::init_objects()
{
	Transform camera_transform;
	camera_transform.location = { 0.0f, -2.0f, 0.0f };
	world.spawn_camera(camera_transform);

	Transform cube_transform;
	cube_transform.scale = { 0.25f, 0.25f, 0.25f };
	cube = world.spawn_mesh_object(cube_transform);;

	Transform cube_transform2;
	cube_transform2.location = { -0.5f, 0.0f, 0.0f };
	cube_transform2.scale = { 0.25f, 0.25f, 0.25f };
	second_cube = world.spawn_mesh_object(cube_transform2);

	Transform floor_transform;
	floor_transform.location = { 0.0f, 0.0f, -0.5f };
	floor_transform.scale = { 7.0f, 30.0f, 0.1f };
	auto floor = world.spawn_mesh_object(floor_transform);

	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material material(shader);
	cube->add_mesh(Buffer_factory::get(Buffer_type::Cube), material);
	second_cube->add_mesh(Buffer_factory::get(Buffer_type::Cube), material);
	floor->add_mesh(Buffer_factory::get(Buffer_type::Cube), material);

	Transform light_transform;
	light_transform.location = { 0.0f, -3.0f, 0.0f };
	world.spawn_light(light_transform);
}

