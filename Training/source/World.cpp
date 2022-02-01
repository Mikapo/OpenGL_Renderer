#include "World.h"

void World::init()
{
  
}

void World::render()
{
    for (auto object : mesh_objects)
        object->render();
}

glm::mat4 World::get_camera_view_matrix()
{
    if (camera)
        return camera->get_view_matrix();
    else
        return glm::mat4(1);
}

glm::mat4 World::get_camera_projection_matrix()
{
    if (camera)
        return camera->get_projection_matrix();
    else
        return glm::mat4(1);
}

std::shared_ptr<Camera> World::spawn_camera(Transform transform)
{
    this->camera.reset(new Camera(this));
    camera->set_transform(transform);
    return this->camera;
}

std::shared_ptr<Mesh_object> World::spawn_mesh_object(Transform transform)
{
    mesh_objects.emplace_back(new Mesh_object(this));
    mesh_objects.back()->set_transform(transform);
    return mesh_objects.back();
}
