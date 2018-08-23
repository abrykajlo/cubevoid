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

	void add_vertices(std::vector<Vertex>&& vs);
	void add_indices(std::vector<GLuint>&& is);
private:
	std::vector<Vertex> vertices_;
	std::vector<GLuint> indices_;

	GLuint vao_;
	GLuint vbo_;
	GLuint vio_;
};

bool Parse(std::basic_istream<char>& is, Mesh& mesh);