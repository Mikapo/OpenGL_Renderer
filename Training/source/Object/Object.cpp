#include "Object.h"


void Object::add_local_offset(glm::vec3 offset)
{
	transform.location += right_vector * offset.x;
	transform.location += forward_vector * offset.y;
	transform.location += up_vector * offset.z;
}

glm::mat4 Object::calulate_rotation_matrix(Rotator rotator)
{
	glm::mat4 identity(1);
	glm::mat4 pitch = glm::rotate(identity, rotator.pitch, glm::vec3(1, 0, 0));
	glm::mat4 yaw = glm::rotate(identity, rotator.yaw, glm::vec3(0, 0, 1));
	glm::mat4 roll = glm::rotate(identity, rotator.roll, glm::vec3(0, 1, 0));
	return roll * yaw * pitch;
}

void Object::update_directional_vectors()
{
	glm::mat4 rotation = calulate_rotation_matrix(get_rotation());

	right_vector = { rotation[0][0], rotation[0][1], rotation[0][2] };
	forward_vector = { rotation[1][0], rotation[1][1], rotation[1][2] };
	up_vector = { rotation[2][0], rotation[2][1], rotation[2][2] };
}
