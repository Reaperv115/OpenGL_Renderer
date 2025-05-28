#pragma once

class OpenGLContext
{
public:
	OpenGLContext(float width, float height, const std::string& windowname);
	OpenGLContext();
	~OpenGLContext();

	int CreateContext(float width, float height, const std::string& windowname);

	inline GLFWwindow* GetWindow() { return window; }
private:
	GLFWwindow* window;
	float _width, _height;
	std::string windowName;
};

