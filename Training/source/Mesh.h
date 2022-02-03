#pragma once

#include <Rendering/Renderer.h>
#include "glm/vec3.hpp"
#include "Transform.h"
#include "Rendering/Material.h"
#include "Rendering/Buffers.h"
#include <memory>

class Mesh_object;
class World;
class Mesh
{
public:
	Mesh(World* world, std::shared_ptr<Buffers> geometry, Material material)
		: world(world), geometry(geometry), material(material) {}

	void render() const;
	void set_relative_rotation(Rotator new_rotation) { relative_transform.rotation = new_rotation; }
	void set_relative_location(glm::vec3 new_location) { relative_transform.location = new_location; }
	void set_relative_scale(glm::vec3 new_scale) { relative_transform.scale = new_scale; }
	void set_relative_transform(Transform new_transform) { relative_transform = new_transform; }
	void set_owner(Mesh_object* new_owner) { owner = new_owner; }
	glm::vec3 get_relative_location() { return relative_transform.location; }
	Rotator get_relative_rotation() { return relative_transform.rotation; }
	glm::vec3 get_relative_scale() { return relative_transform.scale; }
	

private:
	glm::mat4 calculate_model_matrix(Transform transform);

	World* world;
	Mesh_object* owner;
	Renderer renderer;
	std::shared_ptr<Buffers> geometry;
	Material material;
	Transform relative_transform;
};

