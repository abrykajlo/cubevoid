/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "render.h"

#include <core/file.h>
#include <core/quat.h>
#include <render/shader_program.h>

#include <GL/gl.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <cstring>
#include <sstream>

static void
error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

RenderManager::RenderManager() {}

RenderManager::~RenderManager() {}

RenderManager&
RenderManager::GetInstance()
{
    static std::unique_ptr<RenderManager> s_renderManager = nullptr;
    if (s_renderManager == nullptr) {
        s_renderManager = std::make_unique<RenderManager>();
    }
    return *s_renderManager.get();
}

int
RenderManager::Init()
{
    m_log = std::make_unique<Log>("RenderManager.log");
    m_log->Write("write");
    // open window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    m_window = glfwCreateWindow(640, 480, "CubeVoid", nullptr, nullptr);
    if (m_window == nullptr) {
        return -1;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    m_log->Write("GLFW Success");
    // init glew and check for success
    if (glewInit() != GLEW_OK) {
        m_log->Write("GLEW failed to initialize");
        return -1;
    }
    m_log->Write("GLEW initialized");
    glClearColor(0, 0, 0, 1);
    m_initialized = true;

    if (InitShaders() < 0) {
        return -1;
    }
    // not sure if this is the right place for this
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    DefaultReadFile meshFile;
    meshFile.Open("./assets/models/dragon.obj");

    auto size = meshFile.Size();
    char* fileContents = new char[size];
    meshFile.Read(fileContents, size);
    std::istringstream fileContentStream(std::string(fileContents, size));

    if (!Parse(fileContentStream, m_mesh)) {
        m_log->Write("unable to parse file");
        return -1;
    }
    delete[] fileContents;
    m_mesh.Init();

    m_lastTime = m_clock.now();
    return 0;
}

int
RenderManager::Quit()
{
    glfwDestroyWindow(m_window);
    m_mesh.Quit();
    return 0;
}

int
RenderManager::Render()
{
    auto now = m_clock.now();
    auto timeSinceLast = now - m_lastTime;
    std::chrono::milliseconds thirtyFPS(33);
    std::chrono::seconds secondsPerRotation(10);

    if (timeSinceLast >= thirtyFPS) {
        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // rotate at 1 rotation every x seconds
        auto fractionOfFullRotation = secondsPerRotation / timeSinceLast;
        float rad = 2.0f * M_PI / fractionOfFullRotation;
        auto rot = quat_rotation(rad, 0, 1, 0);

        auto& eye = m_mainCamera.eye;
        eye = (rot * quat(eye) * rot.Inverse()).ToVec3();

        // set eye
        glUniform3fv(1, 1, (GLfloat*)&eye);
        // set camera projection
        mat4 projection = m_mainCamera.ViewProjection();
        glUniformMatrix4fv(0, 1, GL_TRUE, (GLfloat*)&projection);

        m_mesh.Draw();
        glfwSwapBuffers(m_window);
        m_lastTime = now;
    }
    return 0;
}

int
RenderManager::InitShaders()
{
    DefaultReadFile vertShaderFile("./assets/shaders/shader.vert");
    DefaultReadFile fragShaderFile("./assets/shaders/shader.frag");

    Shader vertShader(VERTEX_SHADER);
    Shader fragShader(FRAGMENT_SHADER);

    // prepare shader sources
    char buf[1024];
    memset(buf, 0, 1024);
    vertShaderFile.Read(buf, 1024);
    vertShader.SetSource(buf);
    if (vertShader.Compile() < 0) {
        m_log->Write(vertShader.GetError());
        return -1;
    }

    memset(buf, 0, 1024);
    fragShaderFile.Read(buf, 1024);
    fragShader.SetSource(buf);
    if (fragShader.Compile() < 0) {
        m_log->Write(fragShader.GetError());
        return -1;
    }

    // set up shaderprogram
    m_shaderProgram->AttachShader(&vertShader);
    m_shaderProgram->AttachShader(&fragShader);
    if (m_shaderProgram->Link() < 0) {
        m_log->Write(m_shaderProgram->GetError());
        return -1;
    }

    vertShaderFile.Close();
    fragShaderFile.Close();

    m_shaderProgram->Use();
    return 0;
}
