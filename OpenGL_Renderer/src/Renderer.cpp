#include "oglrpch.h"
#include "Renderer.h"
#include "Shader.h"

void GetErrors()
{
	while (glGetError() != GL_NO_ERROR);
}

bool LogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ")" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	Call(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	ib.Bind();
	va.Bind();
	Call(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Draw(const VertexArray& va, const VertexBuffer& vb, const Shader& shader) const
{
	shader.Bind();
	vb.Bind();
	va.Bind();
	Call(glDrawArrays(GL_TRIANGLES, 0, 36));
	Call(glDepthMask(GL_TRUE));
}
