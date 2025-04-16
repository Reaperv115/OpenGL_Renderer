#pragma once
#include "Renderer.h"
class Graphics
{
public:
	Graphics();
	~Graphics();

	int InitializeOpenGL(float width, float height, const std::string& windowName);

	GLFWwindow* GetWindow() const;
private:
	GLFWwindow* window;
	const char* glsl_version = "#version 300 es";
	float _width, _height;
};

