#pragma once

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	unsigned int _id;
	std::string filePath;
	std::unordered_map<std::string, int> uniformlocationCache;
public:
	Shader(const std::string& filepath);
	Shader();
	~Shader();

	void Bind() const;
	void Unbind() const;

	
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void LoadShader(const std::string& filepath);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};

