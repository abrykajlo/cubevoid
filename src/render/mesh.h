#pragma once

#include <render/vertex.h>

#include <GL/glew.h>

#include <vector>


class Mesh
{
public:
	Mesh();
	~Mesh();

	int Init();
	int Quit();

	int Draw();

	void add_vertex(Vertex v);
	void add_index(GLuint i);
private:
	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;

	GLuint vao_;
	GLuint vbo_;
	GLuint vio_;
};

bool Parse(char* from, char* to, Mesh& mesh);