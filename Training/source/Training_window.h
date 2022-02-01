#pragma once

#include "Window.h"

#include "Rendering/Renderer.h"
#include "Mesh.h"
#include <memory>
#include "World.h"

class Training_window : public Window
{
public:
    Training_window() : Window("training") {}

protected:
    void init() override;
    void cleanup() override;
    void update(float deltatime) override; 
    void on_key_pressed(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    void on_window_resize(GLFWwindow* window, int new_width, int new_height) override;
    World* get_world() { return &world; }
private:
    void init_objects();

    World world;
    std::shared_ptr<Mesh_object> cube;
};