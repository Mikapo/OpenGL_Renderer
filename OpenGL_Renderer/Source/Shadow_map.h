#pragma once

#include <glm/mat4x4.hpp>
#include <memory>

#include "Rendering/Texture_slots.h"
#include "Rendering/Buffers.h"

class Light;
class Shader;
class Shadow_map
{
public:
	Shadow_map() {}
	~Shadow_map();

	Shadow_map(const Shadow_map&) = delete;
	Shadow_map(const Shadow_map&&) = delete;
	void operator=(const Shadow_map&) = delete;
	void operator=(const Shadow_map&&) = delete;

	void init(int shadow_width, int shadow_height);
	void bind_frame_buffer() const;
	static void unbind_frame_buffer();
	void bind_texture(Texture_slot slot) const;
	static void unbind_texture();
	void update_model(glm::mat4 model) const;
	std::shared_ptr<Shader> get_shader() const { return m_shader; }
	void get_shadow_resolution(int& out_width, int& out_height) const;

private:
	static unsigned int create_depth_map_texture(int shadow_width, int shadow_height);
	static unsigned int create_frame_buffer(unsigned int depth_map);

	bool m_has_been_initialized = false;
	int m_shadow_width = 0, m_shadow_height = 0;
	std::shared_ptr<Shader> m_shader = nullptr;
	unsigned int m_frame_buffer = 0;
	unsigned int m_depth_map = 0;
};

