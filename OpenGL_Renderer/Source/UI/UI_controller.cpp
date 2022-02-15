#include "UI_controller.h"

#include <iostream>


#include "UI/Elements/Button.h"
#include "UI/Elements/Combo_box.h"
#include "UI/Elements/Checkbox.h"
#include "UI/Elements/Color_picker.h"
#include "UI/Elements/Collapsing_header.h"
#include "UI/Elements/Child_window.h"
#include "UI/Elements/Slider_angle.h"

#include "Rendering/Shader_compiler.h"
#include "Utility/Uniform_names.h"

#include "Renderer_window.h"

void UI_controller::init(GLFWwindow* window)
{
	m_ui.init(window);

	m_ui.add_window_flags(ImGuiWindowFlags_NoResize);
	m_ui.add_window_flags(ImGuiWindowFlags_AlwaysVerticalScrollbar);

	Collapsing_header* header = m_ui.add_chidren<Collapsing_header>("light settings");
	Child_window* light_settings = header->add_children<Child_window>("light_window");
	light_settings->set_border(true);
	light_settings->set_size(0, 400);
	light_settings->set_id(2);

	Color_picker* light_color = light_settings->add_children<Color_picker>("Light color");
	light_color->add_notify(this, &UI_controller::light_color_picker_on_change);

	Slider_angle* light_angle = light_settings->add_children<Slider_angle>("Light angle");
	light_angle->add_notify(this, &UI_controller::light_angle_on_change);
	
	setup_shader_settings();
}

void UI_controller::cleanup()
{
	m_ui.cleanup();
}

void UI_controller::setup_shader_settings()
{
	Collapsing_header* header = m_ui.add_chidren<Collapsing_header>("shader settings");
	Child_window* shader_settings = header->add_children<Child_window>("shader_window");
	shader_settings->set_size(0, 160);
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

void UI_controller::light_color_picker_on_change(glm::vec4 color)
{
	auto light = m_owner->get_light();
	light->set_color(color);
}

