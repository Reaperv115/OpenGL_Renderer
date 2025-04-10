#pragma once


class Player
{
public:
	Player();
	Player(float speed, glm::vec3);
	~Player();

	glm::vec3 GetPosition() const;
	float GetSpeed() const;

	void SetSpeed(float speed);
	void MovePlayer(float dt);
private:
	float _speed;
	glm::vec3 _position;
};

