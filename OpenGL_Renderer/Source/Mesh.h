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
	Mesh(Mesh_object* owner, std::shared_ptr<Buffers> geometry, Material material)
		: m_owner(owner), m_geometry(geometry), m_material(material) {}

	void render() const;
	void render_to_shadow_map(const Shadow_map* shadow_map);
	void set_relative_rotation(Rotator new_rotation) { m_relative_transform.m_rotation = new_rotation; }
	void set_relative_location(glm::vec3 new_location) { m_relative_transform.m_location = new_location; }
	void set_relative_scale(glm::vec3 new_scale) { m_relative_transform.m_scale = new_scale; }
	void set_relative_transform(Transform new_transform) { m_relative_transform = new_transform; }
	glm::vec3 get_relative_location() const { return m_relative_transform.m_location; }
	Rotator get_relative_rotation() const { return m_relative_transform.m_rotation; }
	glm::vec3 get_relative_scale() const { return m_relative_transform.m_scale; }
	

private:
	glm::mat4 calculate_model_matrix() const;
	static glm::mat4 calculate_model_matrix_from_transform(Transform transform);

	Mesh_object* m_owner = nullptr;
	Renderer m_renderer;
	std::shared_ptr<Buffers> m_geometry;
	Material m_material;
	Transform m_relative_transform;
};

