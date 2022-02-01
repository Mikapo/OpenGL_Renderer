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

private:
    World world;
    std::shared_ptr<Mesh_object> cube;
};