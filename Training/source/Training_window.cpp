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
	camera_transform.location = { 0.0f, -1.0f, 0.1f };
	camera_transform.rotation = { 0.0f, 0.0f, 0.0f };
	world.spawn_camera(camera_transform);

	init_walls();
	init_barrels();

	init_furniture();

	Transform light_transform;
	light_transform.location = { 0.0f, -3.0f, 1.0f };
	world.spawn_light(light_transform);
}

void Training_window::init_furniture()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material Gothid_commode(shader);
	Gothid_commode.add_texture(Texture_factory::get("../Textures/GothicCommode.jpg"), 0);
	Gothid_commode.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	Gothid_commode.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	Gothid_commode.diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	Gothid_commode.shininess = { 900.0f };

	Transform furniture_transform;
	furniture_transform.location = { 0.4f, 0.0f, 0.01f };
	furniture_transform.rotation = { 90.0f, -60.0f, 00.0f };
	furniture_transform.scale = { 0.1, 0.1, 0.1 };
	auto furniture = world.spawn_mesh_object(furniture_transform);
	furniture->add_mesh(Buffer_factory::get_from_file("../models/GothicCommode.obj"), Gothid_commode);

	Material Wooden_table(shader);
	Wooden_table.add_texture(Texture_factory::get("../Textures/WoodenTable.jpg"), 0);
	Wooden_table.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	Wooden_table.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	Wooden_table.diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	Wooden_table.shininess = { 900.0f };

	furniture_transform.location = { -0.4f, 0.0f, 0.01f };
	furniture_transform.rotation = { 90.0f, 60.0f, 00.0f };
	furniture_transform.scale = { 0.1, 0.1, 0.1 };
	auto wooden_table = world.spawn_mesh_object(furniture_transform);
	wooden_table->add_mesh(Buffer_factory::get_from_file("../models/WoodenTable.obj"), Wooden_table);
}

void Training_window::init_barrels()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material barrel_material(shader);
	barrel_material.add_texture(Texture_factory::get("../Textures/wine_barrel.jpg"), 0);
	barrel_material.specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	barrel_material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	barrel_material.diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	barrel_material.shininess = { 900.0f };

	Transform barrel_transform;
	barrel_transform.location = { 0.0f, 0.4f, 0.01f };
	barrel_transform.rotation = { 90.0f, 0.0f, 0.0f };
	barrel_transform.scale = { 0.1, 0.1, 0.1 };

	Transform mesh_transform;
	auto barrels = world.spawn_mesh_object(barrel_transform);
	barrels->add_mesh(Buffer_factory::get_from_file("../models/wine_barrel.obj"), barrel_material, mesh_transform);
	mesh_transform.location = { 1.0f, 0.0, 0.0 };
	barrels->add_mesh(Buffer_factory::get_from_file("../models/wine_barrel.obj"), barrel_material, mesh_transform);
	mesh_transform.location = { -1.0f, 0.0, 0.0 };
	barrels->add_mesh(Buffer_factory::get_from_file("../models/wine_barrel.obj"), barrel_material, mesh_transform);
}

void Training_window::init_walls()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/shader.frag", "shaders/Shader.vert");
	Material wall_material(shader);
	wall_material.add_texture(Texture_factory::get("../Textures/stone_tiles.png"), 0);
	wall_material.specular = { 0.1f, 0.1f, 0.1f, 1.0f };
	wall_material.ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	wall_material.shininess = { 100.0f };

	Transform model_transform;
	model_transform.scale = { 0.1f, 0.1f, 0.1f };
	model_transform.rotation = { 0.0f, 0.0f, 0.0f };
	auto wall = world.spawn_mesh_object(model_transform);

	Transform mesh_transform;
	mesh_transform.location = { 0.0f, 0.0f, 0.0f };
	mesh_transform.rotation = { 90.0f, 0.0f, 0.0f };
	mesh_transform.scale = { 1.0f, 1.0f, 1.0f };
	wall->add_mesh(Buffer_factory::get_from_file("../models/wall.obj"), wall_material, mesh_transform);
}

