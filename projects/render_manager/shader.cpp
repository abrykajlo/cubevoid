/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include <utility>

#include "shader.hpp"

Shader::Shader(ShaderType st) 
	: shaderType_(st),
	  error_(nullptr)
{
	GLenum glShaderType;
	switch (st)
	{
	case VERTEX_SHADER:
		glShaderType = GL_VERTEX_SHADER;
		break;
	case TESS_CONTROL_SHADER:
		glShaderType = GL_TESS_CONTROL_SHADER;
		break;
	case TESS_EVALUATION_SHADER:
		glShaderType = GL_TESS_EVALUATION_SHADER;
		break;
	case GEOMETRY_SHADER:
		glShaderType = GL_GEOMETRY_SHADER;
		break;
	case FRAGMENT_SHADER:
		glShaderType = GL_FRAGMENT_SHADER;
		break;
	case COMPUTE_SHADER:
		glShaderType = GL_COMPUTE_SHADER;
		break;
	}
	shaderId_ = glCreateShader(glShaderType);
}

Shader::~Shader()
{
	if (error_ != nullptr)
	{
		delete[] error_;
	}

	if (glIsShader(shaderId_))
	{
		glDeleteShader(shaderId_);
	}
}

void Shader::SetSource(const char* source)
{
	glShaderSource(shaderId_, 1, &source, nullptr);
}

int Shader::Compile()
{
	GLint compileStatus = 0;
	glCompileShader(shaderId_);

	//check compile status
	glGetShaderiv(shaderId_, GL_COMPILE_STATUS, &compileStatus);
	if (!compileStatus)
	{
		return -1;
	}

	return 0;
}

const char* Shader::GetError()
{
	GLint length = 0;
	glGetShaderiv(shaderId_, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		if (errorLength_ < length)
		{
			delete[] error_;
			errorLength_ = length;
			error_ = new char[errorLength_];
		}

		glGetShaderInfoLog(shaderId_, length, nullptr, error_);
		return error_;
	}
	else
	{
		return nullptr;
	}
}