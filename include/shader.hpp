#pragma once

#include <string>

#include <GL/glew.h>

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

	int SetSource(std::string);
	int Compile();
	const char* GetError();
private:
	ShaderType shaderType_;
	std::string source_;
	GLuint shaderId_;
};