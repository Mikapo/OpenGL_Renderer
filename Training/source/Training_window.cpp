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

}

void Training_window::cleanup() 
{ 
	super::cleanup();  
}

void Training_window::update(float deltatime)
{
	world.render();
}

void Training_window::on_key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Transform camera_transform = get_world()->get_current_camera_transform();
	switch (key)
	{
		case GLFW_KEY_E:
		{
			camera_transform.rotation.yaw -= 0.5f * get_delta_seconds();
			break;
		}

		case GLFW_KEY_Q:
		{
			camera_transform.rotation.yaw += 0.5f * get_delta_seconds();
			break;
		}
	}
	get_world()->set_current_camera_transform(camera_transform);

	switch (key)
	{
		case GLFW_KEY_W:
		{
			get_world()->add_current_camera_local_offset(glm::vec3(0, 1, 0) * get_delta_seconds());
			break;
		}

		case GLFW_KEY_S:
		{
			get_world()->add_current_camera_local_offset(glm::vec3(0, -1, 0) * get_delta_seconds());
			break;
		}

		case GLFW_KEY_A:
		{
			get_world()->add_current_camera_local_offset(glm::vec3(-1, 0, 0) * get_delta_seconds());
			break;
		}

		case GLFW_KEY_D:
		{
			get_world()->add_current_camera_local_offset(glm::vec3(1, 0, 0) * get_delta_seconds());
			break;
		}
	}
}

void Training_window::on_window_resize(GLFWwindow* window, int new_width, int new_height)
{
	get_world()->update_aspect_ratio((float)new_width / (float)new_height);
}

void Training_window::init_objects()
{
	Transform camera_transform;
	camera_transform.translation = { 0.0f, -2.0f, 0.0f };
	world.spawn_camera(camera_transform);

	Transform cube_transform;
	cube_transform.scale = { 0.25f, 0.25f, 0.25f };
	auto first_cube = world.spawn_mesh_object(cube_transform);

	Transform cube_transform2;
	cube_transform2.translation = { -0.5f, 0.0f, 0.0f };
	cube_transform2.scale = { 0.25f, 0.25f, 0.25f };
	auto second_cube = world.spawn_mesh_object(cube_transform2);

	Transform cube_transform3;
	cube_transform3.translation = { 0.0f, 0.0f, -0.5f };
	cube_transform3.scale = { 7.0f, 30.0f, 0.1f };
	auto third_cube = world.spawn_mesh_object(cube_transform3);

	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material material(shader);
	first_cube->add_mesh(Cube_buffers::get(), material);
	second_cube->add_mesh(Cube_buffers::get(), material);
	third_cube->add_mesh(Cube_buffers::get(), material);

	Transform light_transform;
	light_transform.translation = { 0.0f, -3.0f, 0.0f };
	world.spawn_light(light_transform);
}

