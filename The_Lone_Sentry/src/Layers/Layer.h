#pragma once
class Layer
{
public:
	Layer(const std::string& name = "Layer");

	virtual void OnAttach(){}
	virtual void OnUpdate(Timer timer){}
	virtual void OnDetach(){}
};

