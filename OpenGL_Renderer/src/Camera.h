#pragma once


#define screen_width 1440
#define screen_height 1080

class Camera
{
public:
	Camera(float left, float right, float bottom, float top, float nearz, float farz);
	~Camera();

	glm::mat4 GetMVPMatrix(const glm::mat4 worldmat) const;
private:
	glm::mat4 modelMatrix, viewMatrix, projectionMatrix;
};
