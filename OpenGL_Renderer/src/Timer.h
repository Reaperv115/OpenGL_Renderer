#pragma once

class Timer
{
public:
	Timer(float dt = 0.0f)
		: _time(dt)
	{

	}

	float GetSeconds() { return _time; }
	float GetMilliseconds() { return _time * 1000; }
private:
	float _time;
};