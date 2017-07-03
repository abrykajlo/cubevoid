#include "shader_program.hpp"

ShaderProgram::ShaderProgram()
	: head_(nullptr),
	tail_(nullptr)
{}

ShaderProgram::~ShaderProgram()
{
	//TODO: need to free up ShaderNodes
}

int ShaderProgram::AddShader(std::shared_ptr<Shader> shader)
{
	if (head_ == nullptr)
	{
		head_ = new ShaderNode(shader);
		tail_ = head_;
	}
	else
	{
		auto temp = new ShaderNode(shader);
		tail_->next = temp;
		tail_ = temp;
	}

	return 0;
}

int ShaderProgram::Compile()
{
	if (head_ == nullptr)
	{
		return -1;
	}
	else
	{
		auto ptr = head_;
		while (ptr->data->Compile() == 0)
		{
			glAttachShader(programId_, ptr->data->shaderId_);
			ptr = ptr->next;
			if (ptr == nullptr) break;
		}

		glLinkProgram(programId_);
	}
	return 0;
}

void ShaderProgram::Use()
{
	glUseProgram(programId_);
}

const char* ShaderProgram::GetError()
{
	return nullptr;
}
