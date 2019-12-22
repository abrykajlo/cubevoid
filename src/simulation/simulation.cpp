/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include <render/render.h>
#include <simulation/simulation.h>

#include <GLFW/glfw3.h>

#include <memory>


SimulationManager::SimulationManager()
{
	//do nothing
}

SimulationManager::~SimulationManager()
{
	//do nothing
}

SimulationManager& SimulationManager::GetInstance()
{
	static std::unique_ptr<SimulationManager> sSimulationManager = nullptr;
	if (sSimulationManager == nullptr)
	{
		sSimulationManager = std::make_unique<SimulationManager>();
	}
	return *sSimulationManager.get();
}

int SimulationManager::Run()
{
	auto& renderManager = RenderManager::GetInstance();
	while (!renderManager.Done())
	{
		renderManager.Render();
	}

	return 0;
}

void SimulationManager::Quit()
{
	m_quit = true;
}

int BigInit()
{
	if (!glfwInit())
	{
		return -1;
	}

	if (RenderManager::GetInstance().Init() < 0)
	{
		return -1;
	}

	return 0;
}

int BigQuit()
{
	if (RenderManager::GetInstance().Quit() < 0)
	{
		return -1;
	}

	glfwTerminate();

	return 0;
}
