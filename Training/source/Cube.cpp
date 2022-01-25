#include "Cube.h"

#include "glm/mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

Cube::~Cube()
{
	if (has_been_initialized)
	{
		delete shader;
		delete va;
		delete vb;
		delete ib;
	}
}

void Cube::init()
{
	if (has_been_initialized)
		throw 1; // cube was intialized twice

	init_buffers();
	init_shader();
	has_been_initialized = true;
}

void Cube::init_buffers()
{
	const float vertices[] =
	{
		 //top
		 0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,

		 //front
		-0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,
	};

	const unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3,

		4, 5, 6,
		4, 6, 7,
	};

	vb = new vertex_buffer(vertices, sizeof(float) * 8 * 7);
	ib = new index_buffer(indices, 12);

	vertex_buffer_layout layout;
	layout.push<float>(3);
	layout.push<float>(4);
	va = new vertex_array();
	va->add_buffer(*vb, layout);
}

void Cube::init_shader()
{
	shader = new Shader("shaders/Shader.frag", "shaders/Shader.vert");
	update_transform();
}

glm::mat4 Cube::calculate_mvp()
{
	glm::mat4 model = glm::mat4(1);
	model *= glm::translate(model, location);
	model *= glm::rotate(model, rotation.pitch, glm::vec3(1, 0, 0));
	model *= glm::rotate(model, rotation.yaw, glm::vec3(0, 0, 1));
	model *= glm::rotate(model, rotation.roll, glm::vec3(0, 1, 0));
	model *= glm::scale(model, scale);

	float eyeloc = 2.0;
	glm::mat4 view = glm::lookAt(glm::vec3(0, -eyeloc, eyeloc), glm::vec3(0, 0, 0), glm::vec3(0, 1, 1));

	glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.f, 1.0f, 100.0f);
	glm::mat4 mvp = projection * view * model;
	return mvp;
}

void Cube::update_transform()
{
	glm::mat4 mvp = calculate_mvp();
	shader->set_uniform_mat4f("u_mvp", mvp);
}

void Cube::render()
{
	if (has_been_initialized)
		renderer.draw(*va, *ib, *shader);
}

void Cube::set_rotation(Rotator new_rotation)
{
	rotation = new_rotation;
	update_transform();
}

void Cube::set_location(glm::vec3 new_location)
{
	location = new_location;
	update_transform();
}

void Cube::set_scale(glm::vec3 new_scale)
{
	scale = new_scale;
	update_transform();
}
