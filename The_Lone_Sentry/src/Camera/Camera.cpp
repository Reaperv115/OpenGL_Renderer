#include "oglrpch.h"
#include "Camera.h"

Camera::Camera()
{
	
}

Camera::~Camera()
{

}

glm::mat4 Camera::GetMVPMatrix(const glm::mat4 worldmat) const
{
	return projectionMatrix * viewMatrix * worldmat;
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::SetViewMatrix(glm::mat4 mat)
{
	viewMatrix = mat;
}

void Camera::SetProjectionMatrix(glm::mat4 mat)
{
	projectionMatrix = mat;
}

glm::mat4 Camera::CreateOrthoCamera(float left, float right, float bottom, float top, float nearz, float farz)
{
	projectionMatrix = glm::ortho(left, right, bottom, top, nearz, farz);
	return projectionMatrix;
}

glm::mat4 Camera::CreatePerspectiveCamera(float fov, float width, float height, float nearz, float farz)
{
	projectionMatrix = glm::perspectiveFovLH(fov, width, height, nearz, farz);
	return projectionMatrix;
}
