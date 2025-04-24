#pragma once
#include "Transform.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
class Missile
{
public:
	Missile(float speed, glm::vec3 position);
	~Missile();

	void MoveMissile(float dt);
	glm::mat4& GetWorldMatrix();
	glm::vec3 GetPosition();
	float* GetVertices();
	unsigned int* GetIndices();
private:
	Transform transform;
	float _speed;
	glm::vec3 _position;
	float vertices[12];
	unsigned int indices[3];
};

