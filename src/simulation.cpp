#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <simulation.h>

SimulationManager::SimulationManager()
{
	SDL_Init(SDL_INIT_EVERYTHING);
}

SimulationManager::~SimulationManager()
{
	SDL_Quit();
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
	}

	return 0;
}

void SimulationManager::Quit()
{
	quit_ = true;
}
