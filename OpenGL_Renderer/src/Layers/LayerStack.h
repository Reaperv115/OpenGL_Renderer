#pragma once
#include "Layer.h"
class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushOverlay(Layer* overlay);
	void PushLayer(Layer* layer);
	void PopOverlay(Layer* overlay);
	void PopLayer(Layer* layer);

	std::vector<Layer*>::iterator iterator;
	std::vector<Layer*>::iterator begin() { return layers.begin(); }
	std::vector<Layer*>::iterator end() { return layers.end(); }
	std::vector<Layer*>::reverse_iterator rbegin() { return layers.rbegin(); }
	std::vector<Layer*>::reverse_iterator rend() { return rend(); }
private:
	std::vector<Layer*> layers;
	unsigned int layerIndex = 0;
};

