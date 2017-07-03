/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include <SDL2/SDL_events.h>
#include <SDL2/SDL.h>
#include <render_manager/render.hpp>

#include "simulation.hpp"

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
				if (event.key.keysym.sym == SDLK_q)
				{
					Quit();
				}
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
