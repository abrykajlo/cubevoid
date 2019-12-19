/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include <render/render.h>
#include <simulation/simulation.h>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>


SimulationManager::SimulationManager()
{
	//do nothing
}

SimulationManager::~SimulationManager()
{
	//do nothing
}

SimulationManager& SimulationManager::GetInstance()
{
	static std::unique_ptr<SimulationManager> sSimulationManager = nullptr;
	if (sSimulationManager == nullptr)
	{
		sSimulationManager = std::make_unique<SimulationManager>();
	}
	return *sSimulationManager.get();
}

int SimulationManager::Run()
{
	while (!m_quit)
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
				if (event.key.keysym.sym == SDLK_q)
				{
					Quit();
				}
			}
		}
		RenderManager::GetInstance().Render();
	}

	return 0;
}

void SimulationManager::Quit()
{
	m_quit = true;
}

int BigInit()
{
	if (RenderManager::GetInstance().Init() < 0)
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
	if (RenderManager::GetInstance().Quit() < 0)
	{
		return -1;
	}

	SDL_Quit();

	return 0;
}
