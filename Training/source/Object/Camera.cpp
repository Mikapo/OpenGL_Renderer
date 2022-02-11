#include "Camera.h"

#include <cmath>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "World.h"

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
    glm::vec3 target_location = current_transform.m_location;
    Rotator target_rotation = current_transform.m_rotation;
    glm::vec3 location = m_camera_transform.m_location;
    Rotator rotation = m_camera_transform.m_rotation;

    float world_distance = glm::distance(location, target_location);
    float rotation_distance = rotation.difference(target_rotation);

    if (world_distance > 0.005 || rotation_distance > 0.005)
    {
        float lerp_amount = 5.0f * deltatime;

        location.x = std::lerp(location.x, target_location.x, lerp_amount);
        location.y = std::lerp(location.y, target_location.y, lerp_amount);
        location.z = std::lerp(location.z, target_location.z, lerp_amount);

        rotation.m_pitch = std::lerp(rotation.m_pitch, target_rotation.m_pitch, lerp_amount);
        rotation.m_yaw = std::lerp(rotation.m_yaw, target_rotation.m_yaw, lerp_amount);
        rotation.m_roll = std::lerp(rotation.m_roll, target_rotation.m_roll, lerp_amount);

        m_camera_transform.m_location = location;
        m_camera_transform.m_rotation = rotation;
        update_matrices();
    }
}

void Camera::set_transform(Transform new_transform)
{
    super::set_transform(new_transform);
    update_matrices();
}

void Camera::set_location(glm::vec3 new_location)
{
    super::set_location(new_location);
    update_matrices();
}

void Camera::set_rotation(Rotator new_rotation)
{
    super::set_rotation(new_rotation);
    update_matrices();
}

void Camera::add_local_offset(glm::vec3 offset)
{
    super::add_local_offset(offset);
    update_matrices();
}

void Camera::add_rotation_offset(Rotator rotation)
{
    super::add_rotation_offset(rotation);
    update_matrices();
}

void Camera::update_matrices()
{
    glm::mat4 rotation = calulate_rotation_matrix(m_camera_transform.m_rotation);

    glm::vec3 cam_pos = m_camera_transform.m_location;
    glm::vec3 cam_norm = { rotation[1][0], rotation[1][1], rotation[1][2] };
    glm::vec3 cam_up = { rotation[2][0], rotation[2][1], rotation[2][2] };

    m_view = glm::lookAt(cam_pos,cam_pos + cam_norm, cam_up);
    m_projection = glm::perspective(glm::radians(m_fow_angle), m_aspect_ratio, m_min_clip, m_max_clip);
}
