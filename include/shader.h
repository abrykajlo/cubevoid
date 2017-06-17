#pragma once

class Shader
{
public:
	Shader();
	~Shader();

	int Compile();
private:
	char* source_;
};

class ShaderProgram
{
	ShaderProgram();
	~ShaderProgram();
};