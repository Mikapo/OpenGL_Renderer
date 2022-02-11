#pragma once

#include "Window.h"

#include <memory>

#include "Mesh.h"
#include "Rendering/Renderer.h"
#include "World.h"

class Training_window : public Window
{
public:
    Training_window() : Window("OpenGL Renderer") {}

protected:
    void init() override;
    void setup_inputs();
    void cleanup() override;
    void update(float deltatime) override; 
    void render() const override;

    void move_camera_right(float value);
    void move_camera_forward(float value);
    void rotate_camera(float value);

    void on_window_resize(GLFWwindow* window, int new_width, int new_height) override;
    World* get_world() { return &m_world; }
private:
    void init_objects();
    void init_furniture();
    void init_barrels();
    void init_walls();

    World m_world;
};