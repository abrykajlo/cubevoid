/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#pragma once

#include <SDL2/SDL_video.h>
#include <core/log.hpp>
#include <core/mesh.hpp>
#include <core/camera.hpp>

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
	Mesh mesh_; //bring mesh out into simulation
	Camera mainCamera_;

	int InitShaders();
};

extern RenderManager gRenderManager;