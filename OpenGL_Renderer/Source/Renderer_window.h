#pragma once

#include "Window.h"

#include <memory>

#include "Mesh.h"
#include "Rendering/Renderer.h"
#include "World.h"
#include "UI/UI_controller.h"

class Renderer_window : public Window
{
public:
    Renderer_window() : Window("OpenGL Renderer"), m_ui_controller(this) {}

    World* get_world() { return &m_world; }
    std::shared_ptr<Light> get_light() const { return m_light; }

protected:
    void init() override;
    void setup_inputs();
    void cleanup() override;
    void update(float deltatime) override;
    void render() override;

    void move_camera_right(float value);
    void move_camera_forward(float value);
    void rotate_camera(float value);

private:
    void init_objects();
    void init_furniture();
    void init_barrels();
    void init_walls();

    World m_world;
    UI_controller m_ui_controller;

    std::shared_ptr<Light> m_light;
};