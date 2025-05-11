#include "oglrpch.h"
#include "LayerStack.h"

LayerStack::LayerStack()
{

}

LayerStack::~LayerStack()
{

}

void LayerStack::PushOverlay(Layer* overlay)
{
	layers.emplace(begin() + layerIndex, overlay);
	layerIndex++;
	overlay->OnAttach();
}

void LayerStack::PushLayer(Layer* layer)
{
	layers.emplace(begin() + layerIndex, layer);
	layerIndex++;
	layer->OnAttach();
}

void LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(begin(), end(), overlay);
	if (it != end())
	{
		overlay->OnDetach();
		layers.erase(it);
		--layerIndex;
	}
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(begin(), end(), layer);
	if (it != end())
	{
		layer->OnDetach();
		layers.erase(it);
		--layerIndex;
	}
}
