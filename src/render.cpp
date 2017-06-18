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


	//open window
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

	//create context for window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	context_ = SDL_GL_CreateContext(window_);
	
	//init glew and check for success
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
	SDL_GL_DeleteContext(context_);
	return 0;
}

RenderManager& RenderManager::Get()
{
	return rm_;
}

RenderManager RenderManager::rm_;