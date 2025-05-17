#include "oglrpch.h"
#include "Renderer.h"
#include "Shader.h"





Renderer::Renderer(float width, float height, const std::string& windowname)
{
	gfx = std::make_shared<Graphics>();
	Init(width, height, windowname);
	std::cout << "Initializing Renderer!" << std::endl;
	PrepareScene();
}

void Renderer::Init(float width, float height, const std::string& windowname)
{
	gfx->InitializeOpenGL(width, height, windowname);}

void Renderer::InitializeGeometry()
{
	triangle.va = std::make_shared<VertexArray>();
	triangle.vb = std::make_shared<VertexBuffer>();
	triangle.ib = std::make_shared<IndexBuffer>();
	triangle.shader = std::make_shared<Shader>();
	triangle.texture = std::make_shared<Texture>();
	triangle.vbl = std::make_shared<VertexBufferLayout>();
	triangle.color = glm::vec3(0.0f, 0.0f, 1.0f);

	square.va = std::make_shared<VertexArray>();
	square.vb = std::make_shared<VertexBuffer>();
	square.ib = std::make_shared<IndexBuffer>();
	square.shader = std::make_shared<Shader>();
	square.texture = std::make_shared<Texture>();
	square.vbl = std::make_shared<VertexBufferLayout>();
	square.color = glm::vec3(0.0f, 0.0f, 1.0f);
}

void Renderer::PrepareGemoetry()
{
	float triangleVerts[] =
	{
		-0.25f, -0.25f, 0.0f, 0.0f, 0.0f,
		0.25f, -0.25f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.25f, 0.0f, 0.5f, 1.0f
	};
	triangle.va->Bind();
	triangle.vb->CreateBuffer(triangleVerts, 3 * 5 * sizeof(float));
	triangle.vbl->Push<float>(3);
	triangle.vbl->Push<float>(2);
	triangle.va->AddBuffer(*triangle.vb, *triangle.vbl);

	unsigned int triangleIndices[] = { 0, 1, 2 };
	triangle.ib->CreateBuffer(triangleIndices, 3);
	triangle.va->AddBuffer(*triangle.ib);

	triangle.color = glm::vec3(0.0f, 0.0f, 1.0f);
	triangle.shader->LoadShader("src/Shaders/Player.shader");
}

void Renderer::PrepareScene()
{
	std::cout << "Preparing Scene!" << std::endl;
	InitializeGeometry();
	PrepareGemoetry();

	triangle.shader->Bind();
	triangle.shader->SetUniform4f("uColor", 0.0f, 0.0f, 1.0f, 1.0f);
	triangle.transform.position = glm::vec3(0.0f, -2.3f, 0.0f);

	triangle.transform.worldMatrix = glm::translate(glm::mat4(1.0f), triangle.transform.position);
	camera.SetViewMatrix(glm::mat4(1.0f));
	camera.SetProjectionMatrix(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f));
	mvp = camera.GetMVPMatrix(triangle.transform.worldMatrix);

	triangle.shader->SetUniformMat4f("mvp", mvp);
}

void Renderer::Update(Timer timer)
{
	std::cout << "Updating Renderer!" << std::endl;
}

void Renderer::Clear()
{
	Call(glClear(GL_COLOR_BUFFER_BIT));
	Call(glClearColor(0.0f, 0.0f, 1.0f, 1.0f));
}

std::shared_ptr<Graphics> Renderer::GetGFX()
{
	return gfx;
}

void Renderer::DrawTriangle()
{
	Call(glDrawElements(GL_TRIANGLES, triangle.ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}
