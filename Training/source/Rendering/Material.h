#pragma once

#include "Rendering/Shader.h"
#include "Transform.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <memory>

class Material
{
public:
	Material(std::shared_ptr<Shader> shader) 
		: shader(shader) {}

	glm::vec4 ambient = { 0.2f, 0.0f, 0.0f, 1.0f };
	glm::vec4 diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	glm::vec4 specular = { 5.0f, 5.0f, 5.0f, 1.0f };
	float shininess = 200.0f;

	void update_shader(glm::mat4 modelview, glm::mat4 projection);
	Shader* get_shader() const { return shader.get(); }

private:
	std::shared_ptr<Shader> shader;

	void update_lighting();
};

