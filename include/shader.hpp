#pragma once

#include <GL/glew.h>
#include <util.hpp>

enum ShaderType
{
	VERTEX_SHADER = GL_VERTEX_SHADER,
	TESS_CONTROL_SHADER = GL_TESS_CONTROL_SHADER,
	TESS_EVALUATION_SHADER = GL_TESS_EVALUATION_SHADER,
	GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
	FRAGMENT_SHADER = GL_FRAGMENT_SHADER,
	COMPUTE_SHADER = GL_COMPUTE_SHADER
};

class Shader
{
public:
	friend class ShaderProgram;

	Shader(ShaderType st);
	~Shader();

	int SetSource(const char*);
	int Compile();
	const char* GetError();
private:
	ShaderType shaderType_;
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