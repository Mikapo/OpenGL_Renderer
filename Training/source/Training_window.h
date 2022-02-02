#pragma once

#include "Window.h"

#include "Rendering/Renderer.h"
#include "Mesh.h"
#include <memory>
#include "World.h"

class Training_window : public Window
{
public:
    Training_window() : Window("OpenGl Renderer") {}

protected:
    void init() override;
    void cleanup() override;
    void update(float deltatime) override; 

    void move_camera_right(float value);
    void move_camera_forward(float value);
    void rotate_camera(float value);

    void on_window_resize(GLFWwindow* window, int new_width, int new_height) override;
    World* get_world() { return &world; }
private:
    void init_objects();

    World world;
    std::shared_ptr<Mesh_object> cube;
};