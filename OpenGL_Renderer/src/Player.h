#pragma once
#include "Transform.h"

	class Player
	{
	public:
		Player();
		Player(float speed, glm::vec3 position);
		~Player();

		glm::vec3 GetPosition() const;
		float GetSpeed() const;

		void SetSpeed(float speed);
		void MovePlayer(float dt);

	private:
		Transform transform;
		glm::vec3 _position;
		float _speed;
		float playerVertices[];
	};


