#include "oglrpch.h"
#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top, float nearz, float farz)
	: modelMatrix(glm::mat4(1.0f)), viewMatrix(glm::mat4(1.0f))
{
	projectionMatrix = glm::ortho(left, right, bottom, top, nearz, farz);
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetMVPMatrix(const glm::mat4 worldmat) const
{
	return projectionMatrix * viewMatrix * worldmat;
}
