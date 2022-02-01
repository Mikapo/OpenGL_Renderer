#include "Object.h"

#include "glm/ext/matrix_transform.hpp"


void Object::add_local_offset(glm::vec3 offset)
{
	transform.translation += forward_vector * offset.y;
	transform.translation += up_vector * offset.z;
	transform.translation += right_vector * offset.x;
}

void Object::update_directional_vectors()
{
	glm::mat4 identity(1);
	glm::mat4 pitch = glm::rotate(identity, transform.rotation.pitch, glm::vec3(1, 0, 0));
	glm::mat4 yaw = glm::rotate(identity, transform.rotation.yaw, glm::vec3(0, 0, 1));
	glm::mat4 roll = glm::rotate(identity, transform.rotation.roll, glm::vec3(0, 1, 0));
	glm::mat4 rotation = roll * yaw * pitch;

	right_vector = { rotation[0][0], rotation[0][1], rotation[0][2] };
	forward_vector = { rotation[1][0], rotation[1][1], rotation[1][2] };
	up_vector = { rotation[2][0], rotation[2][1], rotation[2][2] };
}
