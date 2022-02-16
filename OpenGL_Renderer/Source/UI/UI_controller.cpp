#include "UI_controller.h"

#include <iostream>


#include "UI/Elements/Button.h"
#include "UI/Elements/Combo_box.h"
#include "UI/Elements/Checkbox.h"
#include "UI/Elements/Color_picker.h"
#include "UI/Elements/Parents/Collapsing_header.h"
#include "UI/Elements/Parents/Child_window.h"
#include "UI/Elements/Sliders/Slider_angle.h"
#include "UI/Elements/Sliders/Slider_float.h"

#include "Rendering/Shader_compiler.h"
#include "Utility/Uniform_names.h"

#include "Renderer_window.h"

void UI_controller::init(GLFWwindow* window)
{
	m_ui.init(window);

	UI_window* ui_window = m_ui.add_window("Settings");
	ui_window->add_flag(ImGuiWindowFlags_AlwaysAutoResize);
	ui_window->add_flag(ImGuiWindowFlags_AlwaysVerticalScrollbar);

	Child_window* resize_window = ui_window->add_children<Child_window>("test");
	resize_window->set_id(3);
	resize_window->set_size(300, 1);
	resize_window->add_children<Checkbox>("test");

	setup_camera_settings(ui_window);
	setup_light_settings(ui_window);
	setup_shader_settings(ui_window);
}

void UI_controller::setup_camera_settings(UI_window* window)
{
	Collapsing_header* header = window->add_children<Collapsing_header>("Camera_settings");
	Child_window* camera_settings = header->add_children<Child_window>("camera´window");
	camera_settings->set_id(5);
	camera_settings->set_border(true);
	camera_settings->set_size(300, 100);

	Slider_float* fow = camera_settings->add_children<Slider_float>("fow");
	fow->add_notify(this, &UI_controller::fow_on_change);
	fow->set_max(10.0f);
	fow->set_min(100.0f);
	fow->set_value(30.0f);

	Slider_float* min_clip = camera_settings->add_children<Slider_float>("min_clip");
	min_clip->add_notify(this, &UI_controller::min_clip_on_change);
	min_clip->set_max(40.0f);
	min_clip->set_min(1.0f);
	min_clip->set_value(1.0f);

	Slider_float* max_clip = camera_settings->add_children<Slider_float>("max_clip");
	max_clip->add_notify(this, &UI_controller::max_clip_on_change);
	max_clip->set_max(40.0f);
	max_clip->set_min(1.0f);
	max_clip->set_value(40.0f);
}

void UI_controller::setup_light_settings(UI_window* window)
{
	Collapsing_header* header = window->add_children<Collapsing_header>("Light settings");
	Child_window* light_settings = header->add_children<Child_window>("light window");
	light_settings->set_border(true);
	light_settings->set_size(300, 350);
	light_settings->set_id(2);

	Color_picker* light_color = light_settings->add_children<Color_picker>("Light color");
	light_color->add_notify(this, &UI_controller::light_color_picker_on_change);

	Slider_angle* light_angle = light_settings->add_children<Slider_angle>("Light angle");
	light_angle->add_notify(this, &UI_controller::light_angle_on_change);
}


void UI_controller::setup_shader_settings(UI_window* window)
{
	Collapsing_header* header = window->add_children<Collapsing_header>("Shader settings");
	Child_window* shader_settings = header->add_children<Child_window>("shader window");
	shader_settings->set_size(300, 160);
	shader_settings->set_border(true);
	shader_settings->set_id(1);

	Checkbox* ambient = shader_settings->add_children<Checkbox>("Ambient");
	ambient->add_notify(this, &UI_controller::ambient_checkbox_on_change);

	Checkbox* diffuse = shader_settings->add_children<Checkbox>("Diffuse");
	diffuse->add_notify(this, &UI_controller::diffuse_checkbox_on_change);

	Checkbox* specular = shader_settings->add_children<Checkbox>("Specular");
	specular->add_notify(this, &UI_controller::specular_checkbox_on_change);

	Checkbox* shadow = shader_settings->add_children<Checkbox>("Shadow");
	shadow->add_notify(this, &UI_controller::shadow_checkbox_on_change);

	Checkbox* texture = shader_settings->add_children<Checkbox>("Texture");
	texture->add_notify(this, &UI_controller::texture_checkbox_on_change);

	Checkbox* anti_alias = shader_settings->add_children<Checkbox>("Anti aliasing");
	anti_alias->add_notify(this, &UI_controller::anti_alias_checkbox_on_change);
}

void UI_controller::render()
{
	m_ui.render();
}

void UI_controller::update()
{
	m_ui.check_for_events();
}

void UI_controller::cleanup()
{
	m_ui.cleanup();
}

void UI_controller::ambient_checkbox_on_change(bool enabled)
{
	World* world = m_owner->get_world();
	Shader_settings settings = world->get_shader_settings();
	settings.ambient = enabled;
	world->set_shader_settings(settings);
}

void UI_controller::diffuse_checkbox_on_change(bool enabled)
{
	World* world = m_owner->get_world();
	Shader_settings settings = world->get_shader_settings();
	settings.diffuse = enabled;
	world->set_shader_settings(settings);
}

void UI_controller::specular_checkbox_on_change(bool enabled)
{
	World* world = m_owner->get_world();
	Shader_settings settings = world->get_shader_settings();
	settings.specular = enabled;
	world->set_shader_settings(settings);
}

void UI_controller::shadow_checkbox_on_change(bool enabled)
{
	World* world = m_owner->get_world();
	Shader_settings settings = world->get_shader_settings();
	settings.shadow = enabled;
	world->set_shader_settings(settings);
}

void UI_controller::texture_checkbox_on_change(bool enabled)
{
	World* world = m_owner->get_world();
	Shader_settings settings = world->get_shader_settings();
	settings.texture = enabled;
	world->set_shader_settings(settings);
}

void UI_controller::anti_alias_checkbox_on_change(bool enabled)
{
	World* world = m_owner->get_world();
	Shader_settings settings = world->get_shader_settings();
	settings.anti_alias = enabled;
	world->set_shader_settings(settings);
}

void UI_controller::light_angle_on_change(float degrees)
{
	glm::vec4 original_location = { 0.0f, -4.0f, 3.0f, 1.0f};
	glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>() , degrees, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 new_location = rotation * original_location;

	auto light = m_owner->get_light();
	light->set_location(glm::vec3(new_location) / new_location.w);
}

void UI_controller::fow_on_change(float degrees)
{
	std::shared_ptr<Camera> camera = m_owner->get_camera();
	camera->set_fow_angle(degrees);
}

void UI_controller::min_clip_on_change(float value)
{
	std::shared_ptr<Camera> camera = m_owner->get_camera();
	camera->set_min_clip(value);
}

void UI_controller::max_clip_on_change(float value)
{
	std::shared_ptr<Camera> camera = m_owner->get_camera();
	camera->set_max_clip(value);
}

void UI_controller::light_color_picker_on_change(glm::vec4 color)
{
	auto light = m_owner->get_light();
	light->set_color(color);
}

