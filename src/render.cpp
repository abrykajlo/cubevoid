#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/GL.h>

#include "render.h"

RenderManager::RenderManager()
{
	//do nothing
}

RenderManager::~RenderManager()
{
	//do nothing
}

int RenderManager::Init()
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
	{
		return -1;
	}

	window_ = SDL_CreateWindow("CubeVoid",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL);

	if (window_ == NULL)
	{
		return -1;
	}

	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	SDL_ShowWindow(window_);
	return 0;
}

int RenderManager::Quit()
{
	SDL_DestroyWindow(window_);
	return 0;
}

RenderManager& RenderManager::Get()
{
	return rm_;
}

RenderManager RenderManager::rm_;