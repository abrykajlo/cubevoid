/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#include "mesh.h"

#include <algorithm>


Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

int Mesh::Init()
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(), &vertices_[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)sizeof(vec3));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &vio_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices_.size(), &indices_[0], GL_STATIC_DRAW);

	return 0;
}

int Mesh::Quit()
{
	glBindVertexArray(vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &vio_);
	glDeleteVertexArrays(1, &vao_);
	return 0;
}

int Mesh::Draw()
{
	glBindVertexArray(vao_);
	glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
	return 0;
}

void Mesh::add_vertex(Vertex v)
{
	vertices_.push_back(v);
}

void Mesh::add_index(GLuint i)
{
	indices_.push_back(i);
}

bool Parse(char * from, char * to, Mesh & mesh)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	while (from != to)
	{
		switch (*from)
		{
		case 'v':
			Vertex vert;
			vert.n = { 0, 0, 0 };
			sscanf_s(from, "v %f %f %f", &vert.v.x, &vert.v.y, &vert.v.z);
			vertices.push_back(vert);
			break;
		case 'f':
			GLuint p, q, r;
			sscanf_s(from, "f %d %d %d", &p, &q, &r);
			p--; q--; r--;
			indices.push_back(p);
			indices.push_back(q);
			indices.push_back(r);
		}
		from++;
	}

	std::for_each(vertices.begin(), vertices.end(), [&mesh](Vertex& v) {
		mesh.add_vertex(v);
	});

	std::for_each(indices.begin(), indices.end(), [&mesh](GLuint i) {
		mesh.add_index(i);
	});

	return true;
}
