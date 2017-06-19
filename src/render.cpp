#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/GL.h>
#include <cstdio>

#include "render.h"

RenderManager::RenderManager() : initialized_(false)
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	context_ = SDL_GL_CreateContext(window_);
	
	SDL_GL_SetSwapInterval(1);

	glewExperimental = true;
	//init glew and check for success
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	SDL_ShowWindow(window_);

	initialized_ = true;
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

int RenderManager::Render()
{
	glClearColor(1, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GL_SwapWindow(window_);

	glGetError();
	return 0;
}

RenderManager RenderManager::rm_;