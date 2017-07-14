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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3<float>) * v_.size(), &v_[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

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

void Mesh::add_v(vec3<float> v)
{
	v_.push_back(v);
}

void Mesh::add_f(face f)
{
	f_.push_back(f);
}

bool Parse(char * from, char * to, Mesh & mesh)
{
	vec3<float> v;
	face f;
	while (from != to)
	{
		switch (*from)
		{
		case 'v':
			sscanf_s(from, "v %f %f %f", &v.x, &v.y, &v.z);
			mesh.add_v(v);
			break;
		case 'f':
			sscanf_s(from, "f %d %d %d", &f.x, &f.y, &f.z);
			f.x -= 1; f.y -= 1; f.z -= 1;
			mesh.add_f(f);
		}
		from++;
	}

	return true;
}
