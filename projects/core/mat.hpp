#pragma once

#include <cmath>

#include "vec.hpp"

template <class T, unsigned int M, unsigned int N>
struct mat;

template <class T>
struct mat<T, 2, 2>
{
	T m11, m21;
	T m12, m22;
};

template <class T>
struct mat<T, 3, 3>
{
	T m11, m21, m31;
	T m12, m22, m32;
	T m13, m23, m33;
};

template <class T>
struct mat<T, 4, 4>
{
	T m11, m21, m31, m41;
	T m12, m22, m32, m42;
	T m13, m23, m33, m43;
	T m14, m24, m34, m44;
};

template <class T>
using mat2 = mat<T, 2, 2>;

template <class T>
using mat3 = mat<T, 3, 3>;

template <class T>
using mat4 = mat<T, 4, 4>;

template <int N>
mat<float, N, N> eye();

template<>
mat<float, 2, 2> eye()
{
	return
	{
		1, 0,
		0, 1
	};
}

template<>
mat<float, 3, 3> eye()
{
	return
	{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};
}

template<>
mat<float, 4, 4> eye()
{
	return
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
}