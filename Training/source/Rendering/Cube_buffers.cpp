#include "Cube_buffers.h"

std::weak_ptr<Buffers> Cube_buffers::buffer;

std::shared_ptr<Buffers> Cube_buffers::construct_buffers()
{
	std::array vertices = get_vertex_data();
	std::array indices
	{
		 0,  1,  2,  0,  2,  3, // bottom
		 4,  5,  6,  4,  6,  7, // top
		 8,  9, 10,  8, 10, 11, // left
		12, 13, 14, 12, 14, 15, // rights
		16, 17, 18, 16, 18, 19, // back
		20, 21, 22, 20, 22, 23  // front
	};

	auto vb = new vertex_buffer(vertices.data(), sizeof(float) * (unsigned int)vertices.size());
	auto ib = new index_buffer(indices.data(), (unsigned int)indices.size());

	vertex_buffer_layout layout;
	layout.push<float>(3);
	layout.push<float>(3);

	auto va = new vertex_array();
	va->add_buffer(*vb, layout);

	return std::shared_ptr<Buffers>(new Buffers(vb, va, ib));
}

std::array<float, 144> Cube_buffers::get_vertex_data()
{
	constexpr int amount_of_vertices = 4 * 6;
	constexpr int vertice_dimension = 3;
	constexpr float r = 0.5f;
	constexpr float vertices[amount_of_vertices][vertice_dimension] =
	{
		{ -r, -r, -r }, {  r, -r, -r }, {  r,  r, -r }, { -r,  r, -r }, // bottom
		{ -r, -r,  r }, {  r, -r,  r }, {  r,  r,  r }, { -r,  r,  r }, // top
		{  r, -r, -r }, {  r,  r, -r }, {  r,  r,  r }, {  r, -r,  r }, // left
		{ -r, -r, -r }, { -r,  r, -r }, { -r,  r,  r }, { -r, -r,  r }, // right
		{ -r,  r, -r }, {  r,  r, -r }, {  r,  r,  r }, { -r,  r,  r }, // back
		{ -r, -r, -r }, {  r, -r, -r }, {  r, -r,  r }, { -r, -r,  r }  // front
	};

	constexpr int norm_dimension = 3;
	constexpr float normals[amount_of_vertices][norm_dimension] =
	{
		{ 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, // botton
		{ 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, // top
		{ 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, // left
		{-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, // right
		{ 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, // back
		{ 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}  // front
	};

	// combines vertex and normal buffers
	constexpr int values_per_vertices = vertice_dimension + norm_dimension;
	std::array<float, values_per_vertices* amount_of_vertices> output;
	for (int a = 0; a < amount_of_vertices; a++)
	{
		int offset = 0;
		for (int b = 0; b < vertice_dimension; b++)
			output[offset + b + values_per_vertices * a] = vertices[a][b];

		offset += vertice_dimension;
		for (int b = 0; b < norm_dimension; b++)
			output[offset + b + values_per_vertices * a] = normals[a][b];
	}

	return output;
}

const std::shared_ptr<Buffers> Cube_buffers::get()
{
	if (buffer.expired())
	{
		std::shared_ptr<Buffers> ptr = construct_buffers();
		buffer = ptr;
		return ptr;
	}
	else
		return buffer.lock();
}
