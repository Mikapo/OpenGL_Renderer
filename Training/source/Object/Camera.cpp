#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include "World.h"
#include <iostream>
#include <cmath>

void Camera::init()
{
}

void Camera::update(float deltatime)
{
    lerp_transform(deltatime);
}

void Camera::lerp_transform(float deltatime)
{
    Transform current_transform = get_transform();
    glm::vec3 target_location = current_transform.location;
    Rotator target_rotation = current_transform.rotation;
    glm::vec3 location = camera_transform.location;
    Rotator rotation = camera_transform.rotation;

    if ((location - target_location).length() > 0.001 || rotation.difference(target_rotation) > 0.001)
    {
        float lerp_amount = 5.0f * deltatime;

        location.x = std::lerp(location.x, target_location.x, lerp_amount);
        location.y = std::lerp(location.y, target_location.y, lerp_amount);
        location.z = std::lerp(location.z, target_location.z, lerp_amount);

        rotation.pitch = std::lerp(rotation.pitch, target_rotation.pitch, lerp_amount);
        rotation.yaw = std::lerp(rotation.yaw, target_rotation.yaw, lerp_amount);
        rotation.roll = std::lerp(rotation.roll, target_rotation.roll, lerp_amount);

        camera_transform.location = location;
        camera_transform.rotation = rotation;
        update_matrices();
    }
}

void Camera::set_transform(Transform new_transform)
{
    super::set_transform(new_transform);
    update_matrices();
    get_world()->update_lighting();
}

void Camera::set_location(glm::vec3 new_location)
{
    super::set_location(new_location);
    update_matrices();
    get_world()->update_lighting();
}

void Camera::set_rotation(Rotator new_rotation)
{
    super::set_rotation(new_rotation);
    update_matrices();
    get_world()->update_lighting();
}

void Camera::add_local_offset(glm::vec3 offset)
{
    super::add_local_offset(offset);
    update_matrices();
    get_world()->update_lighting();
}

void Camera::update_matrices()
{
    glm::mat4 rotation = calulate_rotation_matrix(camera_transform.rotation);

    glm::vec3 cam_pos = camera_transform.location;
    glm::vec3 cam_norm = { rotation[1][0], rotation[1][1], rotation[1][2] };
    glm::vec3 cam_up = { rotation[2][0], rotation[2][1], rotation[2][2] };

    view = glm::lookAt(cam_pos,cam_pos + cam_norm, cam_up);

    projection = glm::perspective(glm::radians(fow_angle), aspect_ratio, min_clip, max_clip);
}
