#pragma once

#include <memory>
#include <vector>

#include "Object/Camera.h"
#include "Object/light.h"
#include "Object/Mesh_object.h"
#include "Object/Object.h"
#include "Shadow_map.h"

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

	void update_aspect_ratio(float aspect_ratio) { m_camera->set_aspect_ratio(aspect_ratio); }

private:
	void render_shadow_map() const;
	void update_lighting() const;
	void update_matrices() const;

	std::vector<std::shared_ptr<Mesh_object>> m_mesh_objects;
	std::vector<std::shared_ptr<Light>> m_lights;
	std::shared_ptr<Camera> m_camera;
	Shadow_map m_shadow_map;
};

