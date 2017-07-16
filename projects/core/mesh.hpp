#pragma once

#include <vector>

#include <GL/glew.h>

#include "vertex.hpp"

using face = vec3<int>;

class Mesh
{
public:
	Mesh();
	~Mesh();

	int Init();
	int Quit();

	int Draw();

	void add_vertex(Vertex v);
	void add_face(face f);
private:
	std::vector<Vertex> vertices_;
	std::vector<face> f_;

	GLuint vao_;
	GLuint vbo_;
	GLuint vio_;
};

bool Parse(char* from, char* to, Mesh& mesh);