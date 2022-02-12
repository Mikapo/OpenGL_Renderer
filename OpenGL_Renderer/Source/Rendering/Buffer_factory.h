#pragma once

#include "Renderer.h"


#include <array>
#include <memory>
#include "Buffers.h"

struct aiMesh;
enum Buffer_type
{
	Cube
};

class Buffer_factory
{
public:
	static const std::shared_ptr<Buffers> get_from_file(const std::string& file_path);

private:
	static std::vector<float> get_vertices(aiMesh* mesh);
	static std::vector<unsigned int> get_indices(const aiMesh* mesh);

	static std::unordered_map<std::string, std::weak_ptr<Buffers>> m_buffer_stash;
};

