#include <utility>

#include "shader.hpp"

Shader::Shader(ShaderType st) 
	: shaderType_(st)
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
	const char* csrc = source_.c_str();
	glShaderSource(shaderId_, 1, &csrc, nullptr);
	return 0;
}

int Shader::Compile()
{
	GLint compileSuccess = 0;
	glCompileShader(shaderId_);

	//check compile status
	glGetShaderiv(shaderId_, GL_COMPILE_STATUS, &compileSuccess);
	if (!compileSuccess)
	{
		return -1;
	}

	return 0;
}

const char* Shader::GetError()
{
	GLint length = -1;
	glGetShaderiv(shaderId_, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		//TODO: store length_ and check if resize is necessary
		error_ = new char[length];
		glGetShaderInfoLog(shaderId_, length, nullptr, error_);
		return error_;
	}
	else
	{
		return nullptr;
	}
}