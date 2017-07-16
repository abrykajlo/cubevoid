#include "mat.hpp"

template<>
mat2<float> eye()
{
	return
	{
		1, 0,
		0, 1
	};
}

template<>
mat3<float> eye()
{
	return
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
}

template<>
mat4<float> eye()
{
	return
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}

mat4<float> LookAt(vec3<float> eye, vec3<float> at, vec3<float> up)
{
	auto Z = normalize(at - eye);
	auto X = normalize(cross(Z, up));
	auto Y = cross(X, Z);

	return {
		X.x, X.y, X.z, -dot(X, eye),
		Y.x, Y.y, Y.z, -dot(Y, eye),
		Z.x, Z.y, Z.z, -dot(Z, eye),
		0,   0,   0,            1
	};
}

mat4<float> Frustum(float left, float right, float bottom, float top, float near, float far)
{
	return {
		2 * near / (right - left), 0, (right + left) / (right - left), 0,
		0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
		0, 0, (near + far) / (near - far), 2 * near * far / (near - far),
		0, 0, -1, 0
	};
}