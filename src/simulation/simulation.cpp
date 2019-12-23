/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include <render/render.h>
#include <simulation/simulation.h>

#include <GLFW/glfw3.h>

#include <memory>

static void
error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

SimulationManager::SimulationManager() {}

SimulationManager::~SimulationManager() {}

SimulationManager&
SimulationManager::GetInstance()
{
    static std::unique_ptr<SimulationManager> s_simulationManager = nullptr;
    if (s_simulationManager == nullptr) {
        s_simulationManager = std::make_unique<SimulationManager>();
    }
    return *s_simulationManager.get();
}

int
SimulationManager::Run()
{
    auto& renderManager = RenderManager::GetInstance();
    while (!renderManager.Done()) {
        glfwPollEvents();
        renderManager.Render();
    }

    return 0;
}

int
BigInit()
{
    glfwSetErrorCallback(error_callback);
    glewExperimental = true;
    if (!glfwInit()) {
        return -1;
    }

    if (RenderManager::GetInstance().Init() < 0) {
        return -1;
    }

    return 0;
}

int
BigQuit()
{
    if (RenderManager::GetInstance().Quit() < 0) {
        return -1;
    }

    glfwTerminate();

    return 0;
}
