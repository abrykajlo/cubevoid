/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include <cstring>
#include <cmath>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/GL.h>

#include <core/file.hpp>
#include <core/mat.hpp>

#include "render.hpp"

RenderManager gRenderManager;

RenderManager::RenderManager() 
	: initialized_(false),
	  log_(nullptr)
{
	//do nothing
}

RenderManager::~RenderManager()
{
	//do nothing
}

int RenderManager::Init()
{
	log_ = new Log("RenderManager.log");

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

	if (window_ == nullptr)
	{
		return -1;
	}

	//setup OpenGL version and context profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//create context for window
	context_ = SDL_GL_CreateContext(window_);

	if (context_ == nullptr)
	{
		return -1;
	}

	//init glew and check for success
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	SDL_GL_SetSwapInterval(1);

	SDL_ShowWindow(window_);
	glClearColor(0, 0, 0, 1);
	initialized_ = true;

	if (InitShaders() < 0)
	{
		return -1;
	}
	//not sure if this is the right place for this
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	DefaultReadFile meshFile;
	meshFile.Open("./assets/models/dragon.obj");
	
	auto size = meshFile.Size();
	char* fileContents = new char[size];
	meshFile.Read(fileContents, size);

	if (!Parse(fileContents, fileContents + size - 1, mesh_))
	{
		log_->Write("unable to parse file");
		return -1;
	}
	delete[] fileContents;
	mesh_.Init();
	return 0;
}

int RenderManager::Quit()
{
	SDL_DestroyWindow(window_);
	SDL_GL_DeleteContext(context_);
	delete shaderProgram_;
	mesh_.Quit();
	return 0;
}

int RenderManager::Render()
{
	//clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	auto rad = 0.01;
	mat3<float> roty = {
		cosf(rad), 0, -sinf(rad),
		0, 1, 0,
		sinf(rad), 0, cosf(rad)
	};

	auto& eye = mainCamera_.eye;
	eye = roty * eye;
	
	//set eye
	glUniform3fv(1, 1, (GLfloat*)&eye);
	//set camera projection
	glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&mainCamera_.ViewProjection());

	mesh_.Draw();
	SDL_GL_SwapWindow(window_);
	return 0;
}

int RenderManager::InitShaders()
{
	DefaultReadFile vertShaderFile("./assets/shaders/shader.vert");
	DefaultReadFile fragShaderFile("./assets/shaders/shader.frag");
	
	Shader vertShader(VERTEX_SHADER);
	Shader fragShader(FRAGMENT_SHADER);
	
	//prepare shader sources
	char buf[1024];
	memset(buf, 0, 1024);
	vertShaderFile.Read(buf, 1024);
	vertShader.SetSource(buf);
	if (vertShader.Compile() < 0)
	{
		log_->Write(vertShader.GetError());
		return -1;
	}

	memset(buf, 0, 1024);
	fragShaderFile.Read(buf, 1024);
	fragShader.SetSource(buf);
	if (fragShader.Compile() < 0)
	{
		log_->Write(fragShader.GetError());
		return -1;
	}

	//set up shaderprogram
	shaderProgram_ = new ShaderProgram();
	shaderProgram_->AttachShader(&vertShader);
	shaderProgram_->AttachShader(&fragShader);
	if (shaderProgram_->Link() < 0)
	{
		log_->Write(shaderProgram_->GetError());
		return -1;
	}
	
	vertShaderFile.Close();
	fragShaderFile.Close();
	
	shaderProgram_->Use();
	return 0;
}