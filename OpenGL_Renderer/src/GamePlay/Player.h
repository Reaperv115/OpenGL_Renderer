#pragma once
#include "Transform.h"
#include "Missile.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

	class Player
	{
	public:
		Player();
		Player(float speed, glm::vec3 position);
		~Player();

		glm::vec3 GetPosition() const;
		glm::mat4& GetworldMatrix();
		float GetSpeed() const;
		float* GetPlayerVertices();
		unsigned int* GetPlayerIndices();

		void SetSpeed(float speed);
		void MovePlayer(float dt);

	private:
		Transform transform;
		Missile* missile;
		Camera camera;
		Shader shader;
		Texture texture;

		glm::vec3 _position;
		float _speed;
		float playerVertices[12];
		unsigned int playerIndices[3];
	};


