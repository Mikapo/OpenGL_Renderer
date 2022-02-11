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

	m_world.init();
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
	m_world.update(deltatime);
}

void Training_window::render() const
{
	m_world.render();
}

void Training_window::move_camera_right(float value)
{
	if (value == 0)
		return;

	m_world.add_current_camera_local_offset(glm::vec3(1.0f, 0.0f, 0.0f) * value * get_delta_seconds());
}

void Training_window::move_camera_forward(float value)
{
	if (value == 0)
		return;

	m_world.add_current_camera_local_offset(glm::vec3(0.0f, 1.0f, 0.0f) * value * get_delta_seconds());
}

void Training_window::rotate_camera(float value)
{
	if (value == 0)
		return;

	Rotator m_rotation;
	m_rotation.m_yaw = value * get_delta_seconds();
	m_world.add_current_camera_rotation_offset(m_rotation);
}

void Training_window::on_window_resize(GLFWwindow* window, int new_width, int new_height)
{
	get_world()->update_aspect_ratio((float)new_width / (float)new_height);
}

void Training_window::init_objects()
{
	Transform camera_transform;
	camera_transform.m_location = { 0.0f, -1.0f, 0.1f };
	camera_transform.m_rotation = { 0.0f, 0.0f, 0.0f };
	m_world.spawn_camera(camera_transform);

	init_walls();
	init_barrels();
	init_furniture();

	Transform light_transform;
	light_transform.m_rotation = { 70.0f, 85.0f, -0.0f };
	m_world.spawn_light(light_transform);
}

void Training_window::init_furniture()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/Lighting.frag", "shaders/Lighting.vert");
	Material Gothid_commode(shader);
	Gothid_commode.add_texture(Texture_factory::get("../Textures/GothicCommode.jpg"), Texture_slot::texture);
	Gothid_commode.m_specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	Gothid_commode.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	Gothid_commode.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	Gothid_commode.m_shininess = { 500.0f };

	Transform furniture_transform;
	furniture_transform.m_location = { 0.4f, 0.0f, 0.01f };
	furniture_transform.m_rotation = { 90.0f, -60.0f, 00.0f };
	furniture_transform.m_scale = { 0.1, 0.1, 0.1 };
	auto furniture = m_world.spawn_mesh_object(furniture_transform);
	furniture->add_mesh(Buffer_factory::get_from_file("../models/GothicCommode.obj"), Gothid_commode);

	Material Wooden_table(shader);
	Wooden_table.add_texture(Texture_factory::get("../Textures/WoodenTable.jpg"), Texture_slot::texture);
	Wooden_table.m_specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	Wooden_table.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	Wooden_table.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	Wooden_table.m_shininess = { 900.0f };

	furniture_transform.m_location = { -0.4f, 0.0f, 0.01f };
	furniture_transform.m_rotation = { 90.0f, 60.0f, 00.0f };
	furniture_transform.m_scale = { 0.1, 0.1, 0.1 };
	auto wooden_table = m_world.spawn_mesh_object(furniture_transform);
	wooden_table->add_mesh(Buffer_factory::get_from_file("../models/WoodenTable.obj"), Wooden_table);
}

void Training_window::init_barrels()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/Lighting.frag", "shaders/Lighting.vert");
	Material barrel_material(shader);
	barrel_material.add_texture(Texture_factory::get("../Textures/wine_barrel.jpg"), Texture_slot::texture);
	barrel_material.m_specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	barrel_material.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	barrel_material.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	barrel_material.m_shininess = { 50.0f };

	Transform barrel_transform;
	barrel_transform.m_location = { 0.0f, 0.4f, 0.01f };
	barrel_transform.m_rotation = { 90.0f, 0.0f, 0.0f };
	barrel_transform.m_scale = { 0.1, 0.1, 0.1 };

	Transform mesh_transform;
	auto barrels = m_world.spawn_mesh_object(barrel_transform);
	barrels->add_mesh(Buffer_factory::get_from_file("../models/wine_barrel.obj"), barrel_material, mesh_transform);
	mesh_transform.m_location = { 1.0f, 0.0, 0.0 };
	barrels->add_mesh(Buffer_factory::get_from_file("../models/wine_barrel.obj"), barrel_material, mesh_transform);
	mesh_transform.m_location = { -1.0f, 0.0, 0.0 };
	barrels->add_mesh(Buffer_factory::get_from_file("../models/wine_barrel.obj"), barrel_material, mesh_transform);
}

void Training_window::init_walls()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/Lighting.frag", "shaders/Lighting.vert");
	Material wall_material(shader);
	wall_material.add_texture(Texture_factory::get("../Textures/stone_tiles.png"), Texture_slot::texture);
	wall_material.m_specular = { 0.1f, 0.1f, 0.1f, 1.0f };
	wall_material.m_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	wall_material.m_shininess = { 100.0f };

	Transform model_transform;
	model_transform.m_scale = { 0.1f, 0.1f, 0.1f };
	model_transform.m_rotation = { 0.0f, 0.0f, 0.0f };
	auto wall = m_world.spawn_mesh_object(model_transform);

	Transform mesh_transform;
	mesh_transform.m_location = { 0.0f, 0.0f, 0.0f };
	mesh_transform.m_rotation = { 90.0f, 0.0f, 0.0f };
	mesh_transform.m_scale = { 1.0f, 1.0f, 1.0f };
	wall->add_mesh(Buffer_factory::get_from_file("../models/wall.obj"), wall_material, mesh_transform);
}

