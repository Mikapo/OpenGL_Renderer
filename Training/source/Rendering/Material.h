#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Transform.h"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include <memory>
#include <unordered_map>

class Shader;
class Texture;
class Material
{
public:
	Material(std::shared_ptr<Shader> shader) 
		: shader(shader) {}

	glm::vec4 ambient = { 0.2f, 0.0f, 0.0f, 1.0f };
	glm::vec4 diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	glm::vec4 specular = { 5.0f, 5.0f, 5.0f, 1.0f };
	float shininess = 200.0f;

	void add_texture(std::shared_ptr<Texture> texture, unsigned int slot);
	void bind() const;
	void unbind() const;
	void update_shader(glm::mat4 modelview, glm::mat4 projection) const;

	Shader* get_shader() const { return shader.get(); }

private:
	std::shared_ptr<Shader> shader;
	std::unordered_map<int, std::shared_ptr<Texture>> textures;
	bool has_texture = false;
};

