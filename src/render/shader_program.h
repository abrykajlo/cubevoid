/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#pragma once

#include <core/util.h>
#include <render/shader.h>

#include <memory>


class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	int AttachShader(Shader* shader);
	int Link();
	void Use();
	const char* GetError();
private:
	Shader* shaders_[6];

	GLuint programId_;
	char* error_;
	size_t errorLength_;
};