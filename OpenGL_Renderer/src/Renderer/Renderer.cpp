#include "oglrpch.h"
#include "Renderer.h"
#include "Shader.h"





Renderer::Renderer(float width, float height, const std::string& windowname)
{
	gfx = std::make_shared<Graphics>();
	gfx->InitializeOpenGL(width, height, windowname);
}

void Renderer::Init(float width, float height, const std::string& windowname)
{
	

	
	vbl = std::make_shared<VertexBufferLayout>();

	square = new Square();
	square->va = new VertexArray();
	square->texture = new Texture();
	square->shader = new Shader();

	float squareVertices[5 * 3] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.0f,  0.5f, 0.0f, 0.5f, 1.0f
	};
	vertexBuffer = std::make_shared<VertexBuffer>(squareVertices, sizeof(squareVertices));
	vbl->Push<float>(3);
	vbl->Push<float>(2);
	square->va->AddBuffer(*vertexBuffer, *vbl);

	uint32_t squareIndices[3] = { 0, 1, 2};
	indexBuffer = std::make_shared<IndexBuffer>(squareIndices, sizeof(squareIndices));
	square->va->AddBuffer(*indexBuffer);
	square->va->Unbind();

	//square->texture->LoadTexture("src/textures/other player.png");

	square->shader->LoadShader("src/Shaders/Player.shader");

	square->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Renderer::PrepareScene()
{
	square->transform.worldMatrix = glm::translate(glm::mat4(1.0f), square->transform.position);
	square->transform.worldMatrix = glm::scale(square->transform.worldMatrix, glm::vec3(0.25f, 0.25f, 0.0f));
	camera.SetViewMatrix(glm::mat4(1.0f));
	camera.SetProjectionMatrix(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f));
	mvp = camera.GetMVPMatrix(square->transform.worldMatrix);

	square->shader->Bind();
	square->shader->SetUniformMat4f("mvp", mvp);

	square->texture->Bind();
	square->shader->SetUniform1i("utexture", 0);
}

void Renderer::Update(float dt)
{
	std::cout << dt << std::endl;
	player.Update(dt);
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

void Renderer::DrawQuad()
{
	square->va->Bind();
	square->texture->Bind();
	square->shader->Bind();
	glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw()
{
	DrawQuad();
}
