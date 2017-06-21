#include "shader.hpp"

Shader::Shader(ShaderType st) 
	: source_(nullptr),
	  shaderType_(st)
{
	shaderId_ = glCreateShader(st);
}

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
	glShaderSource(shaderId_, 1, &source, nullptr);
	return 0;
}

int Shader::Compile()
{
	glCompileShader(shaderId_);
	return 0;
}

const char * Shader::GetError()
{
	return nullptr;
}

ShaderProgram::ShaderProgram()
	: head_(nullptr),
	  tail_(nullptr)
{}

ShaderProgram::~ShaderProgram()
{
	//TODO: need to free up ShaderNodes
}

int ShaderProgram::AddShader(Shader& shader)
{
	if (head_ == nullptr)
	{
		head_ = new ShaderNode(&shader);
		tail_ = head_;
	}
	else
	{
		switch (tail_->data->shaderType_)
		{
		case VERTEX_SHADER:
		case TESS_CONTROL_SHADER:
		case TESS_EVALUATION_SHADER:
		case GEOMETRY_SHADER:
		case FRAGMENT_SHADER:
		}
		auto temp = new ShaderNode(&shader);
		tail_->next = temp;
		tail_ = temp;
	}

	return 0;
}

int ShaderProgram::Compile()
{
	return 0;
}

const char* ShaderProgram::GetError()
{
	return nullptr;
}
