#pragma once
#include "OpenGLContext.h"

class Graphics
{
public:
	Graphics(float width, float height, const std::string& windowName);
	Graphics();
	~Graphics();

	int InitializeOpenGL(float width, float height, const std::string& windowName);

	static inline OpenGLContext* GetContext() { return context; }
private:
	static OpenGLContext* context;
	float _width, _height;
	
};
