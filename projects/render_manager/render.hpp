#pragma once

#include <SDL2/SDL_video.h>
#include <core/log.hpp>

#include "shader_program.hpp"


class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	int Init();
	int Quit();

	int Render();
private:
	SDL_Window* window_;
	SDL_GLContext context_;
	bool initialized_;
	Log* log_;
	ShaderProgram* shaderProgram_;
};

extern RenderManager gRenderManager;