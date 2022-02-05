#include "Training_window.h"

#include <iostream>
#include "Rendering/Buffer_factory.h"
#include <unordered_map>
#include "Rendering/Shader_compiler.h"
#include "Rendering/Texture_factory.h"
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
	model->add_rotation_offset(Rotator(0.0f, 1.0f, 0.0f) * deltatime);
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

	Transform model_transform;
	model_transform.scale = { 0.1f, 0.1f, 0.1f };
	model_transform.rotation = { 90.0f, 0.0f, 0.0f };
	model = world.spawn_mesh_object(model_transform);

	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material material(shader);
	material.ambient = { 0.25f, 0.25f, 0.25f, 1.0f };
	model->add_mesh(Buffer_factory::get_from_file("../vader.obj"), material);

	Transform light_transform;
	light_transform.location = { 0.0f, -3.0f, 0.0f };
	world.spawn_light(light_transform);
}

