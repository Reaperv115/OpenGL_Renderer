#include "oglrpch.h"
#include "Graphics.h"


Graphics::Graphics(float width, float height, const std::string& windowName)
	: _width(width), _height(height)
{

	

}

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

int Graphics::InitializeOpenGL(float width, float height, const std::string& windowName)
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

	if (glewInit() != GLEW_OK)
		return -1;
	else
		std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

	Call(glEnable(GL_BLEND));
	Call(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
}

GLFWwindow* Graphics::GetWindow() const
{
	return window;
}
