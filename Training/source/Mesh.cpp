#include "Mesh.h"

#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include <array>
#include <iostream>


void Mesh::render()
{
	material.update_shader(relative_transform);
	renderer.draw(geometry->va.get(), geometry->ib.get(), material.get_shader());
}

void Mesh::set_rotation(Rotator new_rotation)
{
	relative_transform.rotation = new_rotation;
}

void Mesh::set_location(glm::vec3 new_location)
{
	relative_transform.translation = new_location;
}

void Mesh::set_scale(glm::vec3 new_scale)
{
	relative_transform.scale = new_scale;
}
