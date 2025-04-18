#pragma once
#include "transform.h"
#include "Shader.h"

class Enemy
{
public:
	Enemy(glm::vec3 position, float speed);
	~Enemy();

	void MoveEnemy(float dt);
	glm::mat4& GetModelMatrix();
	void SetModelMatrix(glm::mat4& matrix);
	glm::vec3 GetPosition() const;
private:
	Transform transform;
	glm::mat4 modelMatrix;
	glm::vec3 _position;
	float _speed;
};

