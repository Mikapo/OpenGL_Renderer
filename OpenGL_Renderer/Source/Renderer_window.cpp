#include "Renderer_window.h"

#include "GLFW/glfw3.h"

#include <iostream>
#include "Rendering/Model_loader.h"
#include "Rendering/Shader_compiler.h"
#include "Rendering/Texture_loader.h"
#include <unordered_map>

void spawn_models(World* world)
{

}

void Renderer_window::init()
{
	super::init();

	set_debug_messages_enabled(false);
	m_world.init();
	m_ui_controller.init(get_window());
	init_objects();
	setup_inputs();
}

void Renderer_window::setup_inputs()
{
	Input_handler* input_handler = get_input_hanlder();

	Axis_mapping* mapping = input_handler->add_axis_mapping("move_camera_left", this, &Renderer_window::move_camera_right);
	mapping->add_key(GLFW_KEY_A, -1);
	mapping->add_key(GLFW_KEY_D, 1);

	mapping = input_handler->add_axis_mapping("move_camera_right", this, &Renderer_window::move_camera_forward);
	mapping->add_key(GLFW_KEY_S, -1);
	mapping->add_key(GLFW_KEY_W, 1);

	mapping = input_handler->add_axis_mapping("rotate_camera", this, &Renderer_window::rotate_camera);
	mapping->add_key(GLFW_KEY_E, -1);
	mapping->add_key(GLFW_KEY_Q, 1);
}

void Renderer_window::cleanup()
{ 
	super::cleanup();  
}

void Renderer_window::update(float deltatime)
{
	m_world.update(deltatime);
	m_ui_controller.update();
}

void Renderer_window::render()
{
	m_world.render();
	m_ui_controller.render();
}

void Renderer_window::move_camera_right(float value)
{
	if (value == 0)
		return;

	m_world.add_current_camera_local_offset(glm::vec3(5.0f, 0.0f, 0.0f) * value * get_delta_seconds());
}

void Renderer_window::move_camera_forward(float value)
{
	if (value == 0)
		return;

	m_world.add_current_camera_local_offset(glm::vec3(0.0f, 5.0f, 0.0f) * value * get_delta_seconds());
}

void Renderer_window::rotate_camera(float value)
{
	if (value == 0)
		return;

	Rotator m_rotation;
	m_rotation.m_yaw = value * get_delta_seconds();
	m_world.add_current_camera_rotation_offset(m_rotation);
}

void Renderer_window::on_window_resize(GLFWwindow* window, int new_width, int new_height)
{
	m_world.update_screen_size(new_width, new_height);
}

void Renderer_window::init_objects()
{
	Transform camera_transform;
	camera_transform.m_location = { 0.0f, -4.0f, 1.0f };
	m_camera = m_world.spawn_camera(camera_transform);

	init_ground();
	init_furniture();

	Transform light_transform;
	light_transform.m_location = { 0.0f, -5.0f, 5.0f };
	m_light = m_world.spawn_light(light_transform);
}

void Renderer_window::init_furniture()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/Lighting.frag", "shaders/Lighting.vert");
	Material Gothid_commode(shader);
	Gothid_commode.add_texture(Texture_loader::load("../Textures/round_wooden_table.jpg"), Texture_slot::texture);
	Gothid_commode.m_specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	Gothid_commode.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	Gothid_commode.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	Gothid_commode.m_shininess = { 500.0f };

	Transform furniture_transform;
	furniture_transform.m_location = { 4.0f, 0.0f, 0.01f };
	furniture_transform.m_rotation = { 90.0f, -60.0f, 00.0f };
	furniture_transform.m_scale = { 0.75f, 0.75f, 0.75f };
	std::shared_ptr<Mesh_object> furniture = m_world.spawn_mesh_object(furniture_transform);
	furniture->add_meshes(Model_loader::load("../models/round_wooden_table.obj"), Gothid_commode);

	Material Wooden_table(shader);
	Wooden_table.add_texture(Texture_loader::load("../Textures/WoodenTable.jpg"), Texture_slot::texture);
	Wooden_table.m_specular = { 0.5f, 0.5f, 0.5f, 1.0f };
	Wooden_table.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	Wooden_table.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	Wooden_table.m_shininess = { 900.0f };

	Material potted_plant(shader);
	potted_plant.add_texture(Texture_loader::load("../Textures/potted_plant.jpg"), Texture_slot::texture);
	potted_plant.m_specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	potted_plant.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	potted_plant.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	potted_plant.m_shininess = { 700.0f };

	furniture_transform.m_location = { -4.0f, 0.0f, 0.03f };
	furniture_transform.m_rotation = { 90.0f, 60.0f, 00.0f };
	std::shared_ptr<Mesh_object> wooden_table = m_world.spawn_mesh_object(furniture_transform);
	wooden_table->add_meshes(Model_loader::load("../models/WoodenTable.obj"), Wooden_table);

	Transform poted_plant_transform;
	poted_plant_transform.m_location = { 0.1f, 0.55f, 0.1f };
	wooden_table->add_meshes(Model_loader::load("../models/potted_plant.obj"), potted_plant, poted_plant_transform);

	shader = Shader_compiler::get("shaders/Lighting.frag", "shaders/Lighting.vert");
	Material barrel_material(shader);
	barrel_material.add_texture(Texture_loader::load("../Textures/sofa.jpg"), Texture_slot::texture);
	barrel_material.m_specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	barrel_material.m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
	barrel_material.m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	barrel_material.m_shininess = { 50.0f };

	Transform barrel_transform;
	barrel_transform.m_location = { 0.0f, 4.0f, 0.03f };
	barrel_transform.m_rotation = { 90.0f, 0.0f, 0.0f };

	Transform mesh_transform;
	std::shared_ptr<Mesh_object> barrels = m_world.spawn_mesh_object(barrel_transform);
	barrels->add_meshes(Model_loader::load("../models/sofa.obj"), barrel_material, mesh_transform);
}

void Renderer_window::init_ground()
{
	std::shared_ptr<Shader> shader = Shader_compiler::get("shaders/Lighting.frag", "shaders/Lighting.vert");
	Material wall_material(shader);
	wall_material.add_texture(Texture_loader::load("../Textures/wooden_floor.png"), Texture_slot::texture);
	wall_material.m_specular = { 0.9f, 0.9f, 0.9f, 1.0f };
	wall_material.m_ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	wall_material.m_shininess = { 900.0f };

	Transform model_transform;
	model_transform.m_scale = { 0.05f, 0.05f, 0.05f };
	model_transform.m_rotation = { 0.0f, 0.0f, 0.0f };
	std::shared_ptr<Mesh_object> wall = m_world.spawn_mesh_object(model_transform);

	Transform mesh_transform;
	mesh_transform.m_location = { 0.0f, 0.0f, 0.0f };
	mesh_transform.m_rotation = { 90.0f, 0.0f, 0.0f };
	wall->add_meshes(Model_loader::load("../models/wall.obj"), wall_material, mesh_transform);
}

