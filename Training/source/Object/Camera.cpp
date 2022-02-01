#include "Camera.h"

#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

#include "World.h"

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

void Camera::update_matrices()
{
   view = glm::lookAt(get_location(), glm::vec3(0, 0, 0), get_up_vector());
   projection = glm::perspective(glm::radians(30.0f), 1.0f, 1.0f, 300.0f);
}
