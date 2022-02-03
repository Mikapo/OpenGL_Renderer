#pragma once

#include "Object.h"
#include "Mesh.h"

class Mesh_object : public Object
{
public:
	Mesh_object(World* world) : Object(world) {}

	void render() const;
	void add_mesh(std::shared_ptr<Buffers> geometry, Material material, Transform mesh_relative_transform = Transform());

private:
	std::vector<std::unique_ptr<Mesh>> meshes;
};

