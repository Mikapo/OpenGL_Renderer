#include "Buffer_factory.h"

#include <assimp/Importer.hpp>   
#include <assimp/scene.h>      
#include <assimp/postprocess.h> 
#include <vector>
#include <iostream>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices )
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

std::unordered_map<std::string, std::weak_ptr<Buffers>> Buffer_factory::buffer_stash;

const std::shared_ptr<Buffers> Buffer_factory::get_from_file(const std::string& file_path)
{
	if (!buffer_stash[file_path].expired())
		return buffer_stash[file_path].lock();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file_path.c_str(), ASSIMP_LOAD_FLAGS);

	if (!scene)
	{
		std::cout << "file not found";
		std::cin.get();
		throw 1;
	}

	auto mesh = scene->mMeshes[0];
	std::vector<float> vertices = get_vertices(mesh);
	std::vector<unsigned int> indices = get_indices(mesh);
		
	vertex_buffer_layout layout;
	layout.push<float>(3);
	layout.push<float>(3);
	layout.push<float>(2);

	std::shared_ptr buffer = std::shared_ptr<Buffers>(new Buffers(vertices, indices, layout));
	buffer_stash[file_path] = buffer;

	return buffer;
}

std::vector<unsigned int> Buffer_factory::get_indices(const aiMesh* mesh)
{
	int face_amount = mesh->mNumFaces;
	std::vector<unsigned int> indice_array;
	indice_array.reserve(face_amount * 3);

	for (int a = 0; a < face_amount; a++)
	{
		auto face = mesh->mFaces[a];
		for (unsigned int b = 0; b < face.mNumIndices; b++)
		{
			indice_array.push_back(face.mIndices[b]);
		}
	}
	
	return indice_array;
}

std::vector<float> Buffer_factory::get_vertices(aiMesh* mesh)
{
	auto vertices = mesh->mVertices;
	auto normals = mesh->mNormals;
	auto texture_cordinates = mesh->mTextureCoords;
	bool has_texture_cordinates = mesh->HasTextureCoords(0);
	int number_of_vertices = mesh->mNumVertices;

	std::vector<float> vertice_array;
	vertice_array.reserve(number_of_vertices * 9);

	for (int i = 0; i < number_of_vertices; i++)
	{
		vertice_array.push_back(vertices[i].x);
		vertice_array.push_back(vertices[i].y);
		vertice_array.push_back(vertices[i].z);

		vertice_array.push_back(normals[i].x);
		vertice_array.push_back(normals[i].y);
		vertice_array.push_back(normals[i].z);

		aiVector3D texture_coordinate = { 0.0f, 0.0f, 0.0f };
		if (has_texture_cordinates)
			texture_coordinate = texture_cordinates[0][i];

		vertice_array.push_back(texture_coordinate.x);
		vertice_array.push_back(texture_coordinate.y);
	}

	return vertice_array;
}

