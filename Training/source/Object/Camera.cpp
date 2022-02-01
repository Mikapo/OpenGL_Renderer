#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include "World.h"
#include <iostream>

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

void Camera::update_matrices()
{
    glm::vec3 cam_pos = get_location();
    glm::vec3 cam_norm = get_forward_vector();
    glm::vec3 cam_up = get_up_vector();

    view = glm::lookAt(cam_pos,cam_pos + cam_norm, cam_up);

    projection = glm::perspective(glm::radians(fow_angle), aspect_ratio, min_clip, max_clip);
}
