#include "shader.h"

Shader::Shader() : source_(nullptr)
{}

Shader::~Shader()
{
	if (source_ != nullptr)
	{
		delete source_;
	}

	//TODO: delete resource from OpenGL
}

int Shader::SetSource(const char* source)
{
	if (source_ != nullptr)
	{
		delete source_;
	}

	source_ = source;
	return 0;
}

int Shader::Compile()
{
	return 0;
}

const char * Shader::GetError()
{
	return nullptr;
}

ShaderProgram::~ShaderProgram()
{
}

int ShaderProgram::AddShader(Shader & shader)
{
	return 0;
}

int ShaderProgram::Compile()
{
	return 0;
}

const char * ShaderProgram::GetError()
{
	return nullptr;
}
