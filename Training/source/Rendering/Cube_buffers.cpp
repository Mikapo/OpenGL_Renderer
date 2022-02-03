#include "Cube_buffers.h"

#include <assimp/Importer.hpp>   
#include <assimp/scene.h>      
#include <assimp/postprocess.h> 
#include <vector>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices )
#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

std::unordered_map<Buffer_type, std::weak_ptr<Buffers>> Buffer_factory::pre_made_buffers;


const std::shared_ptr<Buffers> Buffer_factory::get_from_file(const std::string& file_path, int mesh_index)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(file_path.c_str(), ASSIMP_LOAD_FLAGS);

	auto vertices = scene->mMeshes[mesh_index]->mVertices;
	auto normals = scene->mMeshes[mesh_index]->mNormals;

	int number_of_vertices = scene->mMeshes[mesh_index]->mNumVertices;

	std::vector<float> vertice_array;
	for (int i = 0; i < number_of_vertices; i++)
	{
		vertice_array.push_back(vertices[i].x);
		vertice_array.push_back(vertices[i].y);
		vertice_array.push_back(vertices[i].z);

		vertice_array.push_back(normals[i].x);
		vertice_array.push_back(normals[i].y);
		vertice_array.push_back(normals[i].z);
	}

	std::vector<unsigned int> indice_array;
	for (int a = 0; a < scene->mMeshes[mesh_index]->mNumFaces; a++)
		for (int b = 0; b < scene->mMeshes[mesh_index]->mFaces[a].mNumIndices; b++)
		{
			indice_array.push_back(scene->mMeshes[mesh_index]->mFaces[a].mIndices[b]);
		}

	vertex_buffer_layout layout;
	layout.push<float>(3);
	layout.push<float>(3);

	return std::shared_ptr<Buffers>(new Buffers(vertice_array, indice_array, layout));
}
