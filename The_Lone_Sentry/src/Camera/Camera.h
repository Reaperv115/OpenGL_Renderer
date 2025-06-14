#pragma once


#define screen_width 1440
#define screen_height 1080

class Camera
{
public:
	Camera();
	~Camera();

	void SetViewMatrix(glm::mat4 mat);
	virtual void SetProjectionMatrix(glm::mat4 mat);

	static glm::mat4 GetMVP(glm::mat4 worldmat);
	static glm::mat4 GetViewMatrix();
	static glm::mat4 GetProjectionMatrix();
	glm::vec3 GetPosition() { return position; }

	glm::mat4 CreateOrthoCamera(float left, float right, float bottom, float top, float nearz, float farz);
	glm::mat4 CreatePerspectiveCamera(float fov, float width, float height, float nearz, float farz);
private:
	static glm::mat4 viewMatrix;
	static glm::mat4 projectionMatrix;
	glm::mat4 mvp;

	static glm::vec3 position;
};
