#include "oglrpch.h"
#include "Graphics.h"


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

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "2D Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
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
