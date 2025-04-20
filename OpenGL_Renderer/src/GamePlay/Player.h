#pragma once
#include "Transform.h"
#include "Missile.h"

	class Player
	{
	public:
		Player();
		Player(float speed, glm::vec3 position);
		~Player();

		glm::vec3 GetPosition() const;
		glm::mat4& GetworldMatrix();
		float GetSpeed() const;

		void SetSpeed(float speed);
		void MovePlayer(float dt);

		Missile* FireMissile(float speed, glm::vec3 position);

	private:
		Transform transform;
		glm::vec3 _position;
		float _speed;
	};


