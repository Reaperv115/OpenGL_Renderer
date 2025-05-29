#include "oglrpch.h"
#include "Renderer.h"
#include "Shader.h"





Renderer::Renderer(float width, float height, const std::string& windowname)
{
	gfx = std::make_shared<Graphics>();
	Init(width, height, windowname);
	std::cout << "Initializing Renderer!" << std::endl;
	BeginScene();
}

void Renderer::Init(float width, float height, const std::string& windowname)
{
	gfx->InitializeOpenGL(width, height, windowname);}

void Renderer::InitializeGeometry()
{
	triangle = new Triangle(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	triangle->va = std::make_shared<VertexArray>();
	triangle->vb = std::make_shared<VertexBuffer>();
	triangle->ib = std::make_shared<IndexBuffer>();
	triangle->vbl = std::make_shared<VertexBufferLayout>();
	triangle->shader = std::make_shared<Shader>();
	triangle->texture = std::make_shared<Texture>();

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
		-0.25f, -0.25f, 0.0f, 0.0f,
		0.25f, -0.25f, 1.0f, 0.0f,
		0.0f, 0.25f, 0.5f, 1.0f
	};
	triangle->va->Bind();
	triangle->vb->CreateBuffer(triangleVerts, 3 * 4 * sizeof(float));
	triangle->vbl->Push<float>(2);
	triangle->vbl->Push<float>(2);
	triangle->va->AddBuffer(*triangle->vb, *triangle->vbl);

	unsigned int triangleIndices[] = { 0, 1, 2 };
	triangle->ib->CreateBuffer(triangleIndices, 3);
	triangle->va->AddBuffer(*triangle->ib);

	triangle->shader->LoadShader("src/Shaders/Player.shader");
	

	triangle->texture->LoadTexture("src/Assets/Textures/other player.png");
	
}

void Renderer::BeginScene()
{
	std::cout << "Preparing Scene!" << std::endl;
	InitializeGeometry();
	PrepareGemoetry();

	// putting object into world space
	triangle->worldMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(triangle->position, 0.0f));

	// setting up camera
	camera.SetViewMatrix(glm::mat4(1.0f));
	camera.SetProjectionMatrix(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f));
	mvp = camera.GetMVPMatrix(triangle->worldMatrix);
	
	triangle->shader->Bind();
	triangle->shader->SetUniformMat4f("mvp", mvp);
	triangle->shader->SetUniform1i("utexture", 0);
	triangle->shader->SetUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
}

void Renderer::Clear()
{
	Call(glClear(GL_COLOR_BUFFER_BIT));
	Call(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
}

std::shared_ptr<Graphics> Renderer::GetGFX()
{
	return gfx;
}

void Renderer::DrawTriangle()
{
	triangle->va->Bind();
	triangle->texture->Bind();
	Call(glDrawElements(GL_TRIANGLES, triangle->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawTriangle(glm::vec2 position,  float rotation)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f))
		* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	triangle->shader->SetUniformMat4f("transform", transform);
	triangle->shader->SetUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
	triangle->va->Bind();
	triangle->texture->Bind();
	Call(glDrawElements(GL_TRIANGLES, triangle->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawTriangle(glm::vec2 position)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	triangle->shader->SetUniformMat4f("transform", transform);
	triangle->va->Bind();
	triangle->texture->Bind();
	Call(glDrawElements(GL_TRIANGLES, triangle->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}
