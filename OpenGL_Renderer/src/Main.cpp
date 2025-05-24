#include "oglrpch.h"
#include "Layers/LayerStack.h"
#include "Layers/GameLayer.h"
#include "Renderer/Renderer.h"
#include "Graphics/Graphics.h"


int main(void)
{  
	Renderer* renderer = new Renderer(screen_width, screen_height, "2D Engine");

	LayerStack layerstack;
	layerstack.PushLayer(new GameLayer());


	float deltaTime = (float)glfwGetTime();
	float prevTime = 0.0f;

	
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(renderer->GetGFX()->GetContext()->GetWindow()))
	{
		Timer timer = deltaTime - prevTime;
		prevTime = deltaTime;
		deltaTime = (float)glfwGetTime();

		for (Layer* layer : layerstack)
		{
			layer->OnUpdate(timer);
		}

		/* Swap front and back buffers */
		Call(glfwSwapBuffers(renderer->GetGFX()->GetContext()->GetWindow()));

		/* Poll for and process events */
		Call(glfwPollEvents());
	}

	

	glfwTerminate();
	return 0;
}