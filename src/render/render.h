/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <core/log.h>
#include <render/camera.h>
#include <render/mesh.h>

#include <GLFW/glfw3.h>

#include <chrono>
#include <memory>

class GLFWwindow;
class ShaderProgram;
class RenderManager
{
  public:
    RenderManager();
    ~RenderManager();

    static RenderManager& GetInstance();

    int Init();
    int Quit();

    int Render();
    inline bool Done() { return glfwWindowShouldClose(m_window); }

  private:
    GLFWwindow* m_window = nullptr;
    bool m_initialized = false;
    std::unique_ptr<Log> m_log;
    std::unique_ptr<ShaderProgram> m_shaderProgram;
    Mesh m_mesh; // bring mesh out into simulation
    Camera m_mainCamera;
    std::chrono::high_resolution_clock m_clock;
    std::chrono::time_point<decltype(m_clock)> m_lastTime;

    int InitShaders();
};
