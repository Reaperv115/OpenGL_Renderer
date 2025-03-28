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

#pragma region Shaders
struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}
#pragma endregion shader stuff

static void GetErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool LogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	Call(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	Call(glShaderSource(id, 1, &src, nullptr));
	Call(glCompileShader(id));

	int result;
	Call(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		Call(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		Call(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
			"shader!" << std::endl;
		std::cout << message << std::endl;
		Call(glDeleteShader(id));
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentShader)
{
	Call(unsigned int program = glCreateProgram());
	Call(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader));
	Call(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

	Call(glAttachShader(program, vs));
	Call(glAttachShader(program, fs));
	Call(glLinkProgram(program));
	Call(glValidateProgram(program));

	Call(glDeleteShader(vs));
	Call(glDeleteShader(fs));

	return program;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	else
		std::cout << "GLFW Version: " << glfwGetVersionString() << std::endl;

	

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
	unsigned int vao;
	Call(glGenVertexArrays(1, &vao));
	Call(glBindVertexArray(vao));

	VertexArray va;
	// creating and binding a vertex buffer
	VertexBuffer vb(triangle, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	

	// creating and binding index buffer
	IndexBuffer ib(indices, 6);

	// reading in shader file
	ShaderProgramSource source = ParseShader("src/Shaders/Basic.glsl");

	// using shaders
	unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
	Call(glUseProgram(shader));

	Call(int location = glGetUniformLocation(shader, "uColor"));
	ASSERT(location != -1);
	Call(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

	float r = 0.0f;
	float increment = 0.5f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Call(glClear(GL_COLOR_BUFFER_BIT));

		Call(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));
		
		va.Bind();
		ib.Bind();

		Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.05f)
			increment = 0.05f;

		r += increment;

		/* Swap front and back buffers */
		Call(glfwSwapBuffers(window));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}
	Call(glDeleteProgram(shader));

	glfwTerminate();
	return 0;
}