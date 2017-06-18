#pragma once

#include <SDL2/SDL_video.h>

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	int Init();
	int Quit();

	static RenderManager& Get();
private:
	static RenderManager rm_;

	SDL_Window* window_;
	SDL_GLContext context_;
};