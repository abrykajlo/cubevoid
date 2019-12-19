/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include "render.h"

#include <core/file.h>
#include <core/quat.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <cstring>
#include <cmath>
#include <sstream>


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

RenderManager& RenderManager::GetInstance()
{
	static std::unique_ptr<RenderManager> sRenderManager = nullptr;
	if (sRenderManager == nullptr)
	{
		sRenderManager = std::make_unique<RenderManager>();
	}
	return *sRenderManager.get();
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
	std::istringstream fileContentStream(std::string(fileContents, size));

	if (!Parse(fileContentStream, mesh_))
	{
		log_->Write("unable to parse file");
		return -1;
	}
	delete[] fileContents;
	mesh_.Init();

	lastTime_ = clock_.now();
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
	auto now = clock_.now();
	auto timeSinceLast = now - lastTime_;
	std::chrono::milliseconds thirtyFPS(33);
	std::chrono::seconds secondsPerRotation(10);

	if (timeSinceLast >= thirtyFPS)
	{
		//clear buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// rotate at 1 rotation every x seconds
		auto fractionOfFullRotation = secondsPerRotation / timeSinceLast;
		float rad = 2.0f * M_PI / fractionOfFullRotation;
		auto rot = quat_rotation(rad, 0, 1, 0);

		auto& eye = mainCamera_.eye;
		eye = (rot * quat(eye) * rot.Inverse()).ToVec3();

		//set eye
		glUniform3fv(1, 1, (GLfloat*)&eye);
		//set camera projection
		mat4 projection = mainCamera_.ViewProjection();
		glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&projection);

		mesh_.Draw();
		SDL_GL_SwapWindow(window_);
		lastTime_ = now;
	}
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