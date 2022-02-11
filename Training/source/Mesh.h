#pragma once

#include <glm/vec3.hpp>
#include <memory>
#include <Rendering/Renderer.h>

#include "Rendering/Buffers.h"
#include "Rendering/Material.h"
#include "Transform.h"


class Mesh_object;
class World;
class Shadow_map;
class Mesh
{
public:
	Mesh(World* world, std::shared_ptr<Buffers> geometry, Material material)
		: m_world(world), m_geometry(geometry), m_material(material) {}

	void render() const;
	void render_to_shadow_map(const Shadow_map* shadow_map);
	void set_relative_rotation(Rotator new_rotation) { m_relative_transform.m_rotation = new_rotation; }
	void set_relative_location(glm::vec3 new_location) { m_relative_transform.m_location = new_location; }
	void set_relative_scale(glm::vec3 new_scale) { m_relative_transform.m_scale = new_scale; }
	void set_relative_transform(Transform new_transform) { m_relative_transform = new_transform; }
	void set_owner(Mesh_object* new_owner) { m_owner = new_owner; }
	glm::vec3 get_relative_location() { return m_relative_transform.m_location; }
	Rotator get_relative_rotation() { return m_relative_transform.m_rotation; }
	glm::vec3 get_relative_scale() { return m_relative_transform.m_scale; }
	

private:
	glm::mat4 calculate_model_matrix() const;
	glm::mat4 calculate_model_matrix_from_transform(Transform transform) const;

	World* m_world;
	Mesh_object* m_owner;
	Renderer m_renderer;
	std::shared_ptr<Buffers> m_geometry;
	Material m_material;
	Transform m_relative_transform;
};

