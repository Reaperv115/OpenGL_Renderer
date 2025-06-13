#include "oglrpch.h"
#include "Camera.h"

glm::mat4 Camera::viewMatrix;
glm::mat4 Camera::projectionMatrix;
glm::vec3 Camera::position;

Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{

}



glm::mat4 Camera::GetMVP(glm::mat4 worldmat)
{
	return projectionMatrix * viewMatrix * worldmat;
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::SetViewMatrix(glm::mat4 mat)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
	viewMatrix = glm::inverse(transform);
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
