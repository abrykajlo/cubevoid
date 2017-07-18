#include <algorithm>

#include "mesh.hpp"

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

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)sizeof(vec3<float>));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &vio_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vio_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face) * f_.size(), &f_[0], GL_STATIC_DRAW);

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
	glDrawElements(GL_TRIANGLES, 3 * f_.size(), GL_UNSIGNED_INT, nullptr);
	return 0;
}

void Mesh::add_vertex(Vertex v)
{
	vertices_.push_back(v);
}

void Mesh::add_face(face f)
{
	f_.push_back(f);
}

bool Parse(char * from, char * to, Mesh & mesh)
{
	std::vector<Vertex> vertices;
	std::vector<face> faces;
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
			face f;
			sscanf_s(from, "f %d %d %d", &f.x, &f.y, &f.z);
			f.x -= 1; f.y -= 1; f.z -= 1;
			faces.push_back(f);
		}
		from++;
	}

	std::for_each(vertices.begin(), vertices.end(), [&mesh](Vertex& v) {
		mesh.add_vertex(v);
	});

	std::for_each(faces.begin(), faces.end(), [&mesh](face& f) {
		mesh.add_face(f);
	});

	return true;
}
