#include "Mesh_object.h"

#include "World.h"


void Mesh_object::render_to_shadow_map(const Shadow_map* shadow_map) const
{
	for (const auto& mesh : m_meshes)
		mesh->render_to_shadow_map(shadow_map);
}

void Mesh_object::render() const
{
	for (const auto& mesh : m_meshes)
		mesh->render();
}

void Mesh_object::add_mesh(std::shared_ptr<Buffers> geometry, Material material, Transform mesh_relative_transform)
{
	m_meshes.emplace_back(new Mesh(get_world(), this, geometry, material));
	m_meshes.back()->set_relative_transform(mesh_relative_transform);
}

void Mesh_object::add_meshes(const std::vector<std::shared_ptr<Buffers>>& geometry, Material material, Transform mesh_relative_transform)
{
	for (auto buffer : geometry)
		add_mesh(buffer, material, mesh_relative_transform);
}
