/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "shader_program.h"

ShaderProgram::ShaderProgram()
    : m_shaders{ nullptr }
{
    m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    if (glIsProgram(m_programId)) {
        glDeleteProgram(m_programId);
    }
}

int
ShaderProgram::AttachShader(Shader* shader)
{
    if (!shader) {
        return -1;
    }

    if (m_shaders[shader->shaderType_]) {
        glDetachShader(m_programId, m_shaders[shader->shaderType_]->shaderId_);
    }

    glAttachShader(m_programId, shader->shaderId_);
    m_shaders[shader->shaderType_].reset(shader);
    return 0;
}

int
ShaderProgram::Link()
{
    GLint linkStatus = 0;
    glLinkProgram(m_programId);

    // check link status
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        return -1;
    }
    return 0;
}

void
ShaderProgram::Use()
{
    glUseProgram(m_programId);
}

const char*
ShaderProgram::GetError()
{
    GLint length = 0;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &length);
    m_error.reserve(length);
    if (length > 0) {
        glGetProgramInfoLog(m_programId, length, nullptr, &m_error[0]);
        return m_error.c_str();
    } else {
        return nullptr;
    }
}
