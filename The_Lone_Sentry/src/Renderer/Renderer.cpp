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
	gfx->InitializeOpenGL(width, height, windowname);
}

void Renderer::InitializeGeometry()
{
	triangle = new Triangle();
	triangle->va = std::make_shared<VertexArray>();
	triangle->vb = std::make_shared<VertexBuffer>();
	triangle->ib = std::make_shared<IndexBuffer>();
	triangle->vbl = std::make_shared<VertexBufferLayout>();
	triangle->TextureShader = std::make_shared<Shader>();
	triangle->colorShader = std::make_shared<Shader>();
	triangle->texture = std::make_shared<Texture>();

	square = new Square();
	square->va = std::make_shared<VertexArray>();
	square->vb = std::make_shared<VertexBuffer>();
	square->ib = std::make_shared<IndexBuffer>();
	square->colorShader = std::make_shared<Shader>();
	square->textureShader = std::make_shared<Shader>();
	square->texture = std::make_shared<Texture>();
	square->vbl = std::make_shared<VertexBufferLayout>();
}

void Renderer::PrepareGemoetry()
{
	float triangleVerts[] =
	{
		-0.25f, -0.25f, 0.0f, 0.0f,
		0.25f, -0.25f, 1.0f, 0.0f,
		0.0f, 0.25f, 0.5f, 1.0f,
	};
	triangle->va->Bind();
	triangle->vb->CreateBuffer(triangleVerts, 3 * 4 * sizeof(float));
	triangle->vbl->Push<float>(2);
	triangle->vbl->Push<float>(2);
	triangle->va->AddBuffer(*triangle->vb, *triangle->vbl);

	unsigned int triangleIndices[] =
	{
		0, 1, 2
	};
	triangle->ib->CreateBuffer(triangleIndices, 3);
	triangle->va->AddBuffer(*triangle->ib);
	

	float squareVerts[] =
	{
		-0.25f, -0.25f, 0.0f, 0.0f,
		0.25f, -0.25f, 1.0f, 0.0f,
		0.25f, 0.25f, 1.0f, 1.0f,
		-0.25f, 0.25f, 0.0f, 1.0f
	};
	square->va->Bind();
	square->vb->CreateBuffer(squareVerts, 4 * 4 * sizeof(float));
	square->vbl->Push<float>(2);
	square->vbl->Push<float>(2);
	square->va->AddBuffer(*square->vb, *square->vbl);

	unsigned int squareIndices[] =
	{
		0, 1, 2,
		2, 3, 0
	};
	square->ib->CreateBuffer(squareIndices, 6);
	square->va->AddBuffer(*square->ib);

	
	
}

void Renderer::BeginScene()
{
	std::cout << "Preparing Scene!" << std::endl;
	InitializeGeometry();
	PrepareGemoetry();


	// setting up camera
	camera.SetViewMatrix(glm::mat4(1.0f));
	camera.SetProjectionMatrix(glm::ortho(-2.5f, 2.5f, -2.5f, 2.5f, -1.0f, 1.0f));

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, -2.3f, 0));
	glm::mat4 mvp = camera.GetMVP(transform);

	triangle->TextureShader->LoadShader("src/Shaders/PLayerTexture.shader");
	triangle->TextureShader->Bind();

	triangle->TextureShader->SetUniformMat4f("mvp", mvp);
	triangle->TextureShader->SetUniform1i("uTexture", 0);
}

void Renderer::Clear()
{
	Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
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

void Renderer::DrawRectangle(glm::vec3 position)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.0f));


	square->colorShader->Bind();
	square->colorShader->SetUniformMat4f("transform", transform);
	square->va->Bind();
	Call(glDrawElements(GL_TRIANGLES, square->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawRectangle(glm::vec3 position, float rotation)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))
		* glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 0, 1));


	square->textureShader->Bind();
	square->textureShader->SetUniformMat4f("transform", transform);
	square->textureShader->SetUniform1i("uTexture", 0);
	square->va->Bind();
	Call(glDrawElements(GL_TRIANGLES, square->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawTriangle(glm::vec3 position, Texture* texture)
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
	triangle->TextureShader->SetUniformMat4f("transform", transform);

	texture->Bind();
	triangle->va->Bind();
	Call(glDrawElements(GL_TRIANGLES, triangle->ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}
