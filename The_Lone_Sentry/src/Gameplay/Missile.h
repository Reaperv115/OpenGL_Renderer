#pragma once
class Missile
{
public:
	Missile();
	~Missile();

	void Init();
	void OnUpdate(Timer timer);
	void Render();
private:
	float speed;
};

