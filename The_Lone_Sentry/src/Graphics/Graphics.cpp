#include "oglrpch.h"
#include "Graphics.h"

OpenGLContext* Graphics::context;
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

	Graphics::context = new OpenGLContext();
	context->CreateContext(width, height, windowName);

	if (glewInit() != GLEW_OK)
		return -1;
	else
		std::cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << std::endl;

	Call(glEnable(GL_BLEND));
	Call(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(context->GetWindow(), true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return 0;
}
