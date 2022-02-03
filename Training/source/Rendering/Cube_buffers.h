#pragma once

#include "Renderer.h"


#include <array>
#include <memory>
#include "Buffers.h"


enum Buffer_type
{
	Cube
};

class Buffer_factory
{
public:
	static const std::shared_ptr<Buffers> get_from_file(const std::string& file_path, int mesh_index = 0);

private:
	struct vertex_data
	{
		vertex_data(std::array<float, 3> location, std::array<float, 3> normal)
			: location(location), normal(normal) {}

		std::array<float, 3> location;
		std::array<float, 3> normal;
	};

	static std::unordered_map<Buffer_type, std::weak_ptr<Buffers>> pre_made_buffers;
};

