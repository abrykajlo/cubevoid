#include <utility>

#include "shader.hpp"

Shader::Shader(ShaderType st) 
	: source_(nullptr),
	  shaderType_(st)
{
	shaderId_ = glCreateShader(st);
}

Shader::~Shader()
{
	//TODO: delete resource from OpenGL
}

int Shader::SetSource(std::string source)
{
	source_ = std::move(source);
	return 0;
}

int Shader::Compile()
{
	glCompileShader(shaderId_);
	return 0;
}

const char* Shader::GetError()
{
	return nullptr;
}