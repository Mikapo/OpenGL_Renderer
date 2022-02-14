#pragma once

#include "Renderer.h"

#include <array>
#include <memory>
#include <vector>

#include "Buffers.h"

struct aiMesh;
struct aiScene;
enum Buffer_type
{
	Cube
};

class Model_loader
{
public:
	static const std::vector<std::shared_ptr<Buffers>> load(const std::string& file_path, int mesh_amount = -1);

private:
	static std::shared_ptr<Buffers> load_mesh_from_scene(const aiScene* scene, int index);
	static std::vector<float> get_vertices(aiMesh* mesh);
	static std::vector<unsigned int> get_indices(const aiMesh* mesh);

};

