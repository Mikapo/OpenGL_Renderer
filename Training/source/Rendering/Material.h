#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <unordered_map>

#include "Shader.h"
#include "Texture.h"
#include "Texture_slots.h"
#include "Transform.h"

class Texture;
class Shader;
class Material
{
public:
	Material(std::shared_ptr<Shader> shader) 
		: m_shader(shader) {}

	glm::vec4 m_ambient = { 0.2f, 0.0f, 0.0f, 1.0f };
	glm::vec4 m_diffuse = { 0.5f, 0.5f, 0.5f, 1.0f };
	glm::vec4 m_specular = { 5.0f, 5.0f, 5.0f, 1.0f };
	float m_shininess = 200.0f;

	void add_texture(std::shared_ptr<Texture> texture, Texture_slot slot);
	void bind() const;
	void unbind() const;
	void update_model(glm::mat4 model) const;

	Shader* get_shader() const { return m_shader.get(); }

private:
	std::shared_ptr<Shader> m_shader;
	std::unordered_map<Texture_slot, std::shared_ptr<Texture>> m_textures;
	bool m_has_texture = false;
};

