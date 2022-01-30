#pragma once

#include "Window.h"

#include "Rendering/Renderer.h"
#include "Mesh.h"
#include <memory>

class Training_window : public Window
{
public:
    Training_window() : Window("training") {}

protected:
    void init() override;
    void cleanup() override;
    void update(double deltatime) override;

private:
    std::unique_ptr<Mesh> cube;
};
