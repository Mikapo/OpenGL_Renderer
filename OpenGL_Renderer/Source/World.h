#pragma once

#include <memory>
#include <vector>

#include "Object/Camera.h"
#include "Object/Light.h"
#include "Object/Mesh_object.h"
#include "Object/Object.h"
#include "Shadow_map.h"

struct Shader_settings
{
	bool ambient = true;
	bool diffuse = true;
	bool specular = true;
	bool shadow = true;
	bool texture = true;
	bool anti_alias = true;
};

class World
{
public:
	void init();
	void update(float deltatime);
	void render() const;

	glm::mat4 get_camera_view_matrix() const;
	glm::mat4 get_camera_projection_matrix() const;

	std::shared_ptr<Camera> spawn_camera(Transform transform = Transform());
	std::shared_ptr<Mesh_object> spawn_mesh_object(Transform transform = Transform());
	std::shared_ptr<Light> spawn_light(Transform transform = Transform());

	void add_current_camera_local_offset(glm::vec3 offset) { m_camera->add_local_offset(offset); }
	void add_current_camera_rotation_offset(Rotator offset) { m_camera->add_rotation_offset(offset); }
	std::shared_ptr<Camera> get_camera() { return m_camera; }

	void update_screen_size(int width, int height);
 
	Shader_settings get_shader_settings() const { return m_shader_settings; };
	void set_shader_settings(Shader_settings settings) { m_shader_settings = settings; }

private:
	void render_shadow_map() const;
	void update_lighting() const;
	void update_matrices() const;

	std::vector<std::shared_ptr<Mesh_object>> m_mesh_objects;
	std::vector<std::shared_ptr<Light>> m_lights;
	std::shared_ptr<Camera> m_camera;
	Shadow_map m_shadow_map;
	Shader_settings m_shader_settings;
	int m_screen_width = 1000, m_screen_height = 1000;
};

