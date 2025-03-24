#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define ASSERT(x) if (!(x)) __debugbreak();
#define Call(x) GetErrors();\
	x;\
	ASSERT(LogCall(#x, __FILE__, __LINE__))

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
		char* message = (char*)alloca(length * sizeof(char));
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
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

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

	// creating and binding a vertex buffer
	unsigned int buffer;
	Call(glGenBuffers(1, &buffer));
	Call(glBindBuffer(GL_ARRAY_BUFFER, buffer));
	Call(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), triangle, GL_STATIC_DRAW));
	
	// enabling vertex buffer
	Call(glEnableVertexAttribArray(0));
	Call(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

	// creating and binding index buffer
	unsigned int ibo;
	Call(glGenBuffers(1, &ibo));
	Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

	// reading in shader file
	ShaderProgramSource source = ParseShader("src/Basic.glsl");

	// using shaders
	unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
	Call(glUseProgram(shader));

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		Call(glClear(GL_COLOR_BUFFER_BIT));

		// NOTE: if not appearing correctly, check for possible GL_INT
		// instead of GL_UNSIGNED_INT
		Call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


		/* Swap front and back buffers */
		Call(glfwSwapBuffers(window));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}
	Call(glDeleteProgram(shader));

	glfwTerminate();
	return 0;
}