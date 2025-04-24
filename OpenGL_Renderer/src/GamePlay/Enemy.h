#pragma once
#include "transform.h"
#include "Shader.h"

class Enemy
{
public:
	Enemy(glm::vec3 position, float speed);
	~Enemy();

	void MoveEnemy(float dt);
	void SetModelMatrix(glm::mat4& matrix);
	void StopTriangle(bool stopped);
	bool IsStopped();
	glm::vec3 GetPosition() const;
	glm::mat4& GetRotation();
	float* GetVertices();
	unsigned int* GetIndices();
private:
	Transform transform;
	glm::vec3 _position;
	float _speed;
	bool isStopped;
	float Vertices[12];
	unsigned int Indices[3];
};

