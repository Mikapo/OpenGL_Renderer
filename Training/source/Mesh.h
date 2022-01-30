#pragma once

#include <Rendering/Renderer.h>
#include "glm/vec3.hpp"
#include "Transform.h"
#include "Rendering/Material.h"
#include "Rendering/Buffers.h"
#include <memory>

class Mesh
{
public:
	Mesh(std::shared_ptr<Buffers> geometry, Material material)
		: geometry(geometry), material(material) {}

	void render();
	void set_rotation(Rotator new_rotation);
	void set_location(glm::vec3 new_location);
	void set_scale(glm::vec3 new_rotation);
	glm::vec3 get_location() { return relative_transform.translation; }
	Rotator get_rotation() { return relative_transform.rotation; }
	glm::vec3 get_scale() { return relative_transform.scale; }

private:
	Renderer renderer;
	std::shared_ptr<Buffers> geometry;
	Material material;
	Transform relative_transform;
};

