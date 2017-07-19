/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include "shader_program.h"


ShaderProgram::ShaderProgram()
	: shaders_{nullptr},
	  error_(nullptr),
	  errorLength_(0)
{
	programId_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	if (error_)
	{
		delete[] error_;
	}

	if (glIsProgram(programId_))
	{
		glDeleteProgram(programId_);
	}
}

int ShaderProgram::AttachShader(Shader* shader)
{
	if (!shader)
	{
		return -1;
	}
	
	if (shaders_[shader->shaderType_])
	{
		glDetachShader(programId_, shaders_[shader->shaderType_]->shaderId_);
	}
	
	glAttachShader(programId_, shader->shaderId_);
	shaders_[shader->shaderType_] = shader;
	return 0;
}

int ShaderProgram::Link()
{
	GLint linkStatus = 0;
	glLinkProgram(programId_);

	//check link status
	glGetProgramiv(programId_, GL_LINK_STATUS, &linkStatus);
	if (!linkStatus)
	{
		return -1;
	}
	return 0;
}

void ShaderProgram::Use()
{
	glUseProgram(programId_);
}

const char* ShaderProgram::GetError()
{
	GLint length = 0;
	glGetProgramiv(programId_, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		if (errorLength_ < length)
		{
			delete[] error_;
			errorLength_ = length;
			error_ = new char[errorLength_];
		}

		glGetProgramInfoLog(programId_, length, nullptr, error_);
		return error_;
	}
	else
	{
		return nullptr;
	}
}
