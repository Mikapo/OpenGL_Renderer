#include "Training_window.h"

#include <iostream>
#include "Rendering/Cube_buffers.h"

void Training_window::init()
{
	super::init();

	auto shader = std::shared_ptr<Shader>(new Shader("shaders/Shader.frag", "shaders/Shader.vert"));
	Material material(shader);
	cube.reset(new Mesh(Cube_buffers::get(), material));
	cube->set_scale({ 0.5, 0.5, 0.5 });
}

void Training_window::cleanup() 
{ 
	super::cleanup();  
}

void Training_window::update(double deltatime)
{
	auto rotation = cube->get_rotation();
	rotation.yaw += 0.25f * deltatime;
	cube->set_rotation(rotation);

	cube->render();
}
