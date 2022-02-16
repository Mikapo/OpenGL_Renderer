#pragma once

#include "UI.h"

#include "glm/vec4.hpp"
#include <string>

struct GLFWwindow;
class Renderer_window;
class UI_controller 
{
public:
    UI_controller(Renderer_window* owner) : m_owner(owner), m_ui("settings") {}

    void init(GLFWwindow* window);
    void cleanup();
    void render();
    void update();

    void ambient_checkbox_on_change(bool enabled);
    void diffuse_checkbox_on_change(bool enabled);
    void specular_checkbox_on_change(bool enabled);
    void shadow_checkbox_on_change(bool enabled);
    void texture_checkbox_on_change(bool enabled);
    void anti_alias_checkbox_on_change(bool enabled);

    void light_color_picker_on_change(glm::vec4 color);
    void light_angle_on_change(float degrees);

    void fow_on_change(float degrees);
    void min_clip_on_change(float value);
    void max_clip_on_change(float value);

private:
    void setup_camera_settings(UI_window* window);
    void setup_light_settings(UI_window* window);
    void setup_shader_settings(UI_window* window);

    Renderer_window* m_owner;
    UI m_ui;

};
