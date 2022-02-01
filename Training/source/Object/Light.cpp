#include "light.h"

#include "World.h"

void Light::set_transform(Transform new_transform)
{
	super::set_transform(new_transform);
	get_world()->on_lighting_change(this);
}

void Light::set_location(glm::vec3 new_location)
{
	super::set_location(new_location);
	get_world()->on_lighting_change(this);
}

void Light::set_rotation(Rotator new_rotation)
{
	super::set_rotation(new_rotation);
	get_world()->on_lighting_change(this);
}
