#pragma once

#include "Renderer.h"


#include <array>
#include <memory>
#include "Buffers.h"

class Cube_buffers
{
public:
	static const std::shared_ptr<Buffers> get();
private:
	static std::shared_ptr<Buffers> construct_buffers();
	static std::array<float, 144> get_vertex_data();

	static std::weak_ptr<Buffers> buffer;
};

