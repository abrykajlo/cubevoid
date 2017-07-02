#pragma once

#include <memory>

#include <shader.hpp>
#include <util.hpp>

using ShaderNode = Node<std::shared_ptr<Shader>>;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	int AddShader(std::shared_ptr<Shader> shader);
	int Compile();
	void Use();
	const char* GetError();
private:
	ShaderNode* head_;
	ShaderNode* tail_;

	GLuint programId_;
};