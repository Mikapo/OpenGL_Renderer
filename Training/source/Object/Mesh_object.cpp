#include "Mesh_object.h"

#include "World.h"

void Mesh_object::render()
{
	for (auto& mesh : meshes)
		mesh->render();
}

void Mesh_object::add_mesh(std::shared_ptr<Buffers> geometry, Material material, Transform mesh_relative_transform)
{
	meshes.emplace_back(new Mesh(get_world(), geometry, material));
	meshes.back()->set_relative_transform(mesh_relative_transform);
	meshes.back()->set_owner(this);
}