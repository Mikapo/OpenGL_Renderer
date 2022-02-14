#include "Shadow_map.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "Object/Light.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/Shader_compiler.h"

Shadow_map::~Shadow_map()
{
	if (m_has_been_initialized)
	{
		glDeleteTextures(1, &m_depth_map);
		glDeleteFramebuffers(1, &m_frame_buffer);
	}
}

void Shadow_map::init(int shadow_width, int shadow_height)
{
	if (m_has_been_initialized)
		return;

	m_shadow_width = shadow_width;
	m_shadow_height = shadow_height;

	m_shader = Shader_compiler::get("shaders/Shadow_map.frag", "shaders/Shadow_map.vert");
	m_depth_map = create_depth_map_texture(shadow_width, shadow_height);
	m_frame_buffer = create_frame_buffer(m_depth_map);
	m_has_been_initialized = true;
}

unsigned int Shadow_map::create_depth_map_texture(int shadow_width, int shadow_height) const
{
	unsigned int depth_map; 
	glGenTextures(1, &depth_map); 
	glBindTexture(GL_TEXTURE_2D, depth_map);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadow_width, shadow_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_DEPTH_TO_TEXTURE_EXT);
	glBindTexture(GL_TEXTURE_2D, 0); 
	return depth_map; 
}

unsigned int Shadow_map::create_frame_buffer(unsigned int depth_map) const
{
	unsigned int frame_buffer;
	glGenFramebuffers(1, &frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return frame_buffer;
}

void Shadow_map::bind_frame_buffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer);
}

void Shadow_map::unbind_frame_buffer() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Shadow_map::bind_texture(Texture_slot slot) const
{
	glActiveTexture(GL_TEXTURE0 + (int)slot);
	glBindTexture(GL_TEXTURE_2D, m_depth_map);
}

void Shadow_map::unbind_texture() const
{
	glBindTexture(GL_TEXTURE_2D, 9);
}

void Shadow_map::update_model(glm::mat4 model) const
{
	m_shader->bind();
	m_shader->set_uniform_mat4f("u_model", model);
	m_shader->unbind();
}

void Shadow_map::get_shadow_resolution(int& out_width, int& out_height) const
{
	out_width = m_shadow_width;
	out_height = m_shadow_height;
}
