#include "Object.h"


void Object::add_local_offset(glm::vec3 offset)
{
	m_transform.m_location += m_right_vector * offset.x;
	m_transform.m_location += m_forward_vector * offset.y;
	m_transform.m_location += m_up_vector * offset.z;
}

glm::mat4 Object::calulate_rotation_matrix(Rotator rotator)
{
	glm::mat4 identity(1);
	glm::mat4 pitch = glm::rotate(identity, rotator.m_pitch, glm::vec3(1, 0, 0));
	glm::mat4 yaw = glm::rotate(identity, rotator.m_yaw, glm::vec3(0, 0, 1));
	glm::mat4 roll = glm::rotate(identity, rotator.m_roll, glm::vec3(0, 1, 0));
	return roll * yaw * pitch;
}

void Object::update_directional_vectors()
{
	glm::mat4 rotation = calulate_rotation_matrix(get_rotation());

	m_right_vector = { rotation[0][0], rotation[0][1], rotation[0][2] };
	m_forward_vector = { rotation[1][0], rotation[1][1], rotation[1][2] };
	m_up_vector = { rotation[2][0], rotation[2][1], rotation[2][2] };
}
