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
#include "Graphics/Graphics.h"
#include "Enemy.h"


bool show_demo_window = true;
bool show_another_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



int main(void)
{
	

	glm::vec3 positionA(0.0f, -2.2f, 0.0f);
	Player player(5.0f, positionA);

	


	
	

	Graphics gfx;
	gfx.InitializeOpenGL(screen_width, screen_height, "2D Engine");
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	

	float Player[] =
	{
	   -0.25f, -0.25f, 0.0f, 0.0f, // 0
		0.25f, -0.25f, 1.0f, 0.0f, // 1
		0.0f,  0.25f, 0.5f, 1.0f, // 2
	};

	unsigned int playerIndices[] =
	{
		0, 1, 2
	};

	float enemyVertices[] =
	{
		-0.25f, -0.25f, 0.0f, 0.0f, // 0
		0.25f, -0.25f, 1.0f, 0.0f, // 1
		0.0f,  0.25f, 0.5f, 1.0f, // 2
	};

	unsigned int enemyIndices[] =
	{
		0, 2, 1
	};
	

	

	VertexArray va;
	Camera camera;

	


	// player
	VertexBuffer vb(Player, 3 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(playerIndices, 3);
	Shader shader("src/Shaders/Basic.shader");
	shader.Bind();

	Texture texture("src/Textures/other player.png");
	texture.Bind();
	shader.SetUniform1i("uTexture", 0);

	// Enemy*
	VertexBuffer enemyBuffer(enemyVertices, 3 * 4 * sizeof(float));

	VertexBufferLayout enemyLayout;
	enemyLayout.Push<float>(2);
	enemyLayout.Push<float>(2);
	va.AddBuffer(enemyBuffer, enemyLayout);

	glm::vec3 enemyPosition(-2.2f, 2.1f, 0.0f);

	IndexBuffer enemyIB(enemyIndices, 3);
	Shader enemyShader("src/Shaders/Enemy.shader");
	enemyShader.Bind();
	
	Enemy enemy(enemyPosition, 5.0f);
	enemy.GetModelMatrix() = glm::translate(glm::mat4(1.0f), enemyPosition);
	enemy.GetModelMatrix() = glm::rotate(enemy.GetModelMatrix(), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	enemy.GetModelMatrix() = glm::scale(enemy.GetModelMatrix(), glm::vec3(0.25f, 0.25f, 0.0f)); 
	shader.SetUniformMat4f("mvp", enemy.GetModelMatrix());
	enemyShader.SetUniform4f("uColor", 0.0f, 0.0f, 1.0f, 1.0f);


	Renderer renderer;

	
	

	std::chrono::steady_clock::time_point lastUpdate, currentUpdate;
	float deltaTime;
	lastUpdate = std::chrono::steady_clock::now();
	
	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(gfx.GetWindow()))
	{
		currentUpdate = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(currentUpdate - lastUpdate).count() / 1000000.0f;
		lastUpdate = currentUpdate;
		/* Render here */
		renderer.Clear();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (GetAsyncKeyState('A'))
		{
			std::cout << deltaTime << std::endl;
			player.MovePlayer(-deltaTime);
			// Do stuff
		}
		if (GetAsyncKeyState('D'))
		{
			std::cout << deltaTime << std::endl;
			player.MovePlayer(deltaTime);
		}
		

		enemy.MoveEnemy(deltaTime);
		


		shader.Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), player.GetPosition());
		camera.SetViewMatrix(glm::mat4(1.0f));
		camera.SetProjectionMatrix(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f, -1.0f, 1.0f));
		glm::mat4 mvp = camera.GetMVPMatrix(model);
		shader.SetUniformMat4f("mvp", mvp);
		shader.SetUniform1i("uTexture", 0);
		renderer.Draw(va, ib, shader);

		enemyShader.Bind();
		enemy.GetModelMatrix() = glm::translate(glm::mat4(1.0f), enemy.GetPosition());
		enemy.GetModelMatrix() = glm::rotate(enemy.GetModelMatrix(), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		enemy.GetModelMatrix() = glm::scale(enemy.GetModelMatrix(), glm::vec3(0.25f, 0.25f, 0.0f));
		camera.SetViewMatrix(glm::mat4(1.0f));
		camera.SetProjectionMatrix(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f));
		mvp = camera.GetMVPMatrix(enemy.GetModelMatrix());
		enemyShader.SetUniformMat4f("mvp", mvp);
		enemyShader.SetUniform4f("uColor", 0.0f, 0.0f, 1.0f, 1.0f);
		renderer.Draw(va, enemyIB, enemyShader);
		

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
		Call(glfwSwapBuffers(gfx.GetWindow()));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}