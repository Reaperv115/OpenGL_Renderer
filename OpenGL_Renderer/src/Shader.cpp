#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& filepath)
	: filePath(filepath), _id(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	_id = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader()
{
	Call(glDeleteProgram(_id));
}

unsigned int Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentShader)
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

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
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

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
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

void Shader::Bind() const
{
	Call(glUseProgram(_id));
}

void Shader::Unbind() const
{
	Call(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	Call(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	Call(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	Call(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (uniformlocationCache.find(name) != uniformlocationCache.end())
		return uniformlocationCache[name];

	Call(unsigned int location = glGetUniformLocation(_id, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist" << std::endl;

	uniformlocationCache[name] = location;
	return location;
}
