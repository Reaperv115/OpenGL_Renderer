#include "oglrpch.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Player.h"


bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



int main(void)
{
	GLFWwindow* window;
	const char* glsl_version = "#version 300 es";

	glm::vec3 positionA(0.0f, -2.2f, 0.0f);
	Player player(5.0f, positionA);

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	else
		std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screen_width, screen_height, "2D Engine", NULL, NULL);
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
		std::cout << "GLEW Version: " <<  glewGetString(GLEW_VERSION) << std::endl;

	float triangle[] =
	{
	   -0.25f, -0.25f, 0.0f, 0.0f, // 0
		0.25f, -0.25f, 1.0f, 0.0f, // 1
		0.0f,  0.25f, 0.5f, 1.0f, // 2
	};

	unsigned int indices[] =
	{
		0, 1, 2
	};

	Call(glEnable(GL_BLEND));
	Call(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


	VertexArray va;
	VertexBuffer vb(triangle, 3 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 3);
	
	Camera camera(-2.5f, 2.5f, -2.5f, 2.5f, -1.0f, 1.0f);

	Shader shader("src/Shaders/Basic.shader");
	shader.Bind();

	Texture texture("src/Textures/other player.png");
	texture.Bind();
	shader.SetUniform1i("uTexture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// TODO: create deltatime for player movement

	std::chrono::steady_clock::time_point lastUpdate, currentUpdate;
	float deltaTime;
	lastUpdate = std::chrono::steady_clock::now();
	
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		currentUpdate = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentUpdate - lastUpdate).count() / 1000000.0f;
		lastUpdate = currentUpdate;
		/* Render here */
		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (GetAsyncKeyState('A') & 0x8000)
		{
			std::cout << deltaTime << std::endl;
			player.MovePlayer(-deltaTime);
			// Do stuff
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			std::cout << deltaTime << std::endl;
			player.MovePlayer(deltaTime);
		}

		shader.Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), player.GetPosition());
			glm::mat4 mvp = camera.GetMVPMatrix(model);
			shader.SetUniformMat4f("mvp", mvp);
			renderer.Draw(va, ib, shader);
		}

		static float f = 0.0f;
		static int counter = 0;

		// creating a window in ImGui
		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		ImGui::Render();
		ImGui::EndFrame();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		Call(glfwSwapBuffers(window));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}