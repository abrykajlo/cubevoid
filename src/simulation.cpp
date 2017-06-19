#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <simulation.h>
#include <render.h>

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
	RenderManager& rm = RenderManager::Get();
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
		rm.Render();
	}

	return 0;
}

void SimulationManager::Quit()
{
	quit_ = true;
}

int BigInit()
{
	auto rm = RenderManager::Get();

	if (rm.Init() < 0)
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
	auto rm = RenderManager::Get();

	if (rm.Quit() < 0)
	{
		return -1;
	}

	SDL_Quit();

	return 0;
}
