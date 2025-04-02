#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	else
		std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "2D Engine", NULL, NULL);
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
	   -0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
	   -0.5f,  0.5f,
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};


	VertexArray va;
	VertexBuffer vb(triangle, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 6);
	
	Shader shader("src/Shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("uColor", 0.8f, 0.3f, 0.8f, 1.0f);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	float r = 0.0f;
	float increment = 0.5f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Call(glClear(GL_COLOR_BUFFER_BIT));

		shader.Bind();
		shader.SetUniform4f("uColor", r, 0.3f, 0.8f, 1.0f);
		
		ib.Bind();
		va.Bind();

		Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.05f)
			increment = 0.05f;

		r += increment;
		std::cout << r << std::endl;

		/* Swap front and back buffers */
		Call(glfwSwapBuffers(window));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}

	glfwTerminate();
	return 0;
}