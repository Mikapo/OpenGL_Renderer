#pragma once

#include <vector>
#include <memory>
#include "Object/Object.h"
#include "Object/Camera.h"
#include "Object/Mesh_object.h"
#include "Object/light.h"

class World
{
public:
	void init();
	void render();
	void on_lighting_change(Light* light);

	glm::mat4 get_camera_view_matrix();
	glm::mat4 get_camera_projection_matrix();

	std::shared_ptr<Camera> spawn_camera(Transform transform = Transform());
	std::shared_ptr<Mesh_object> spawn_mesh_object(Transform transform = Transform());
	std::shared_ptr<Light> spawn_light(Transform transform = Transform());

private:
	std::vector<std::shared_ptr<Mesh_object>> mesh_objects;
	std::vector<std::shared_ptr<Light>> lights;
	std::shared_ptr<Camera> camera;
};

