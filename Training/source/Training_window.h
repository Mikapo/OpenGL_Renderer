#pragma once

#include "Window.h"

#include "Rendering/Renderer.h"
#include "Cube.h"

class Training_window : public Window
{
public:
    Training_window() : Window("training") {}

protected:
    void init() override;
    void cleanup() override;
    void update() override;

private:
    Cube cube;
};
