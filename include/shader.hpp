#pragma once

#include <GL/glew.h>
#include <util.hpp>

class Shader
{
public:
	friend class ShaderProgram;

	Shader();
	~Shader();

	int SetSource(const char*);
	int Compile();
	const char* GetError();
private:
	const char* source_;
	GLuint shaderId_;
};

using ShaderNode = Node<Shader*>;

class ShaderProgram
{
	ShaderProgram();
	~ShaderProgram();

	int AddShader(Shader& shader);
	int Compile();
	const char* GetError();
private:
	ShaderNode* head_;
	ShaderNode* tail_;

	GLuint programId_;
};