#include "oglrpch.h"
#include "Renderer/Renderer.h"
#include "VertexBuffer.h"
#include "Graphics/Graphics.h"
#include "Timer.h"
#include "Layers/LayerStack.h"
#include "Layers/GameLayer.h"



int main(void)
{  
	Renderer renderer(screen_width, screen_height, "2D Engine");

	LayerStack layerstack;
	layerstack.PushLayer(new GameLayer());

	// initializes graphics

	float deltaTime = (float)glfwGetTime();
	float prevTime = 0.0f;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(renderer.GetGFX()->GetWindow()))
	{
		Timer timer = deltaTime - prevTime;
		prevTime = deltaTime;
		deltaTime = (float)glfwGetTime();
		for (Layer* layer : layerstack)
		{
			layer->OnUpdate(timer);
		}

		/* Swap front and back buffers */
		Call(glfwSwapBuffers(renderer.GetGFX()->GetWindow()));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}

	

	glfwTerminate();
	return 0;
}