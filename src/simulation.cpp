#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <simulation.h>
#include <render.h>

RenderManager gRenderManager;

SimulationManager::SimulationManager()
{
	//do nothing
}

SimulationManager::~SimulationManager()
{
	//do nothing
}

int SimulationManager::Run()
{
	while (!quit_)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) 
			{
				Quit();
			}

			if (event.type == SDL_KEYDOWN) 
			{
				Quit();
			}
		}
		gRenderManager.Render();
	}

	return 0;
}

void SimulationManager::Quit()
{
	quit_ = true;
}

int BigInit()
{
	if (gRenderManager.Init() < 0)
	{
		return -1;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return -1;
	}

	return 0;
}

int BigQuit()
{
	if (gRenderManager.Quit() < 0)
	{
		return -1;
	}

	SDL_Quit();

	return 0;
}
