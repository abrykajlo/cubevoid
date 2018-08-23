/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#pragma once

#include <core/log.h>
#include <render/mesh.h>
#include <render/camera.h>
#include <render/shader_program.h>

#include <SDL2/SDL_video.h>

#include <chrono>


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
	std::chrono::high_resolution_clock clock_;
	std::chrono::time_point<decltype(clock_)> lastTime_;

	int InitShaders();
};

extern RenderManager gRenderManager;