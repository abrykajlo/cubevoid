#pragma once

#include <vector>

#include <GL/glew.h>

#include "vec.hpp"

using face = vec3<int>;

class Mesh
{
public:
	Mesh();
	~Mesh();

	int Init();
	int Quit();

	int Draw();

	void add_v(vec3<float> v);
	void add_f(face f);
private:
	std::vector<vec3<float>> v_;
	std::vector<face> f_;

	GLuint vao_;
	GLuint vbo_;
	GLuint vio_;
};

bool Parse(char* from, char* to, Mesh& mesh);