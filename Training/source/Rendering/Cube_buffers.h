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
	static const std::shared_ptr<Buffers> get(Buffer_type type);
	static const std::shared_ptr<Buffers> get_from_file(const std::string file_path);

private:
	static std::shared_ptr<Buffers> construct_buffers();
	static std::array<float, 144> get_vertex_data();

	static std::weak_ptr<Buffers> buffer;
};

