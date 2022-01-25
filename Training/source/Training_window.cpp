#include "Training_window.h"



void Training_window::init()
{
	super::init();

	cube.init();
	cube.init();
}

void Training_window::cleanup() 
{ 
	super::cleanup();  
}

void Training_window::update()
{ 
	Rotator rotation = cube.get_rotation();
	rotation.pitch += 0.001;
	cube.set_rotation(rotation);
	cube.render();
}
