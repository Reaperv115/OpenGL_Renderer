#pragma once


#define screen_width 1440
#define screen_height 1080

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 GetMVPMatrix(const glm::mat4 worldmat) const;
	glm::mat4 GetViewMatrix();
	void SetViewMatrix(glm::mat4 mat);
	virtual void SetProjectionMatrix(glm::mat4 mat);

	glm::mat4 CreateOrthoCamera(float left, float right, float bottom, float top, float nearz, float farz);
	glm::mat4 CreatePerspectiveCamera(float fov, float width, float height, float nearz, float farz);
protected:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 mvp;
};
