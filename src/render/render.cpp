/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include "render.h"

#include <core/file.h>
#include <core/quat.h>
#include <render/shader_program.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cstring>
#include <cmath>
#include <sstream>


RenderManager::RenderManager() 
{
}

RenderManager::~RenderManager()
{
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
	m_log = new Log("RenderManager.log");

	//open window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	m_window = glfwCreateWindow(640, 480, "CubeVoid", nullptr, nullptr);
	if (m_window == nullptr)
	{
		return -1;
	}

	glfwSwapInterval(1);

	//init glew and check for success
	if (glewInit() != GLEW_OK)
	{
		return -1;
	}

	glClearColor(0, 0, 0, 1);
	m_initialized = true;

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

	if (!Parse(fileContentStream, m_mesh))
	{
		m_log->Write("unable to parse file");
		return -1;
	}
	delete[] fileContents;
	m_mesh.Init();

	m_lastTime = m_clock.now();
	return 0;
}

int RenderManager::Quit()
{
	glfwDestroyWindow(m_window);
	delete m_shaderProgram;
	m_mesh.Quit();
	return 0;
}

int RenderManager::Render()
{
	auto now = m_clock.now();
	auto timeSinceLast = now - m_lastTime;
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

		auto& eye = m_mainCamera.eye;
		eye = (rot * quat(eye) * rot.Inverse()).ToVec3();

		//set eye
		glUniform3fv(1, 1, (GLfloat*)&eye);
		//set camera projection
		mat4 projection = m_mainCamera.ViewProjection();
		glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&projection);

		m_mesh.Draw();
		glfwSwapBuffers(m_window);
		m_lastTime = now;
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
		m_log->Write(vertShader.GetError());
		return -1;
	}

	memset(buf, 0, 1024);
	fragShaderFile.Read(buf, 1024);
	fragShader.SetSource(buf);
	if (fragShader.Compile() < 0)
	{
		m_log->Write(fragShader.GetError());
		return -1;
	}

	//set up shaderprogram
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->AttachShader(&vertShader);
	m_shaderProgram->AttachShader(&fragShader);
	if (m_shaderProgram->Link() < 0)
	{
		m_log->Write(m_shaderProgram->GetError());
		return -1;
	}
	
	vertShaderFile.Close();
	fragShaderFile.Close();
	
	m_shaderProgram->Use();
	return 0;
}
