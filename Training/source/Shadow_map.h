#pragma once

#include <glm/mat4x4.hpp>
#include <memory>

#include "Rendering/Texture_slots.h"

class Light;
class Shader;
class Shadow_map
{
public:
	~Shadow_map();

	void init(int shadow_width, int shadow_height);
	void bind_frame_buffer() const; 
	void unbind_frame_buffer() const;
	void bind_texture(Texture_slot slot) const;
	void unbind_texture() const;
	void update_model(glm::mat4 model) const;
	std::shared_ptr<Shader> get_shader() const { return m_shader; }

private:
	unsigned int create_depth_map_texture(int shadow_width, int shadow_height) const;
	unsigned int create_frame_buffer(unsigned int depth_map) const;

	bool m_has_been_initialized = false;
	int m_shadow_width, m_shadow_height;
	std::shared_ptr<Shader> m_shader;
	unsigned int m_frame_buffer;
	unsigned int m_depth_map;
};

