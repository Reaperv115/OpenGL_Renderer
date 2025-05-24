#include "oglrpch.h"
#include "OpenGLContext.h"

OpenGLContext::OpenGLContext(float width, float height, const std::string& windowname)
{
	
}

OpenGLContext::OpenGLContext()
{

}

OpenGLContext::~OpenGLContext()
{

}

int OpenGLContext::CreateContext(float width, float height, const std::string& windowname)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	else
		std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed to initialize window" << std::endl;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	return 0;
}
