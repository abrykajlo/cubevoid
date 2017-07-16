#pragma once

#include <cmath>

#include "vec.hpp"

template <class T>
struct mat2
{
	T m11, m12;
	T m21, m22;
};

template <class T>
struct mat3
{
	T m11, m12, m13;
	T m21, m22, m23;
	T m31, m32, m33;
};

template <class T>
struct mat4
{
	T m11, m12, m13, m14;
	T m21, m22, m23, m24;
	T m31, m32, m33, m34;
	T m41, m42, m43, m44;
};

template <class MatT>
MatT eye();

template <class T>
mat4<T> operator*(const mat4<T>& M1, const mat4<T>& M2)
{
	return {
		M1.m11*M2.m11 + M1.m12*M2.m21 + M1.m13*M2.m31 + M1.m14*M2.m41,
		M1.m11*M2.m12 + M1.m12*M2.m22 + M1.m13*M2.m32 + M1.m14*M2.m42,
		M1.m11*M2.m13 + M1.m12*M2.m23 + M1.m13*M2.m33 + M1.m14*M2.m43,
		M1.m11*M2.m14 + M1.m12*M2.m24 + M1.m13*M2.m34 + M1.m14*M2.m44,
		M1.m21*M2.m11 + M1.m22*M2.m21 + M1.m23*M2.m31 + M1.m24*M2.m41,
		M1.m21*M2.m12 + M1.m22*M2.m22 + M1.m23*M2.m32 + M1.m24*M2.m42,
		M1.m21*M2.m13 + M1.m22*M2.m23 + M1.m23*M2.m33 + M1.m24*M2.m43,
		M1.m21*M2.m14 + M1.m22*M2.m24 + M1.m23*M2.m34 + M1.m24*M2.m44,
		M1.m31*M2.m11 + M1.m32*M2.m21 + M1.m33*M2.m31 + M1.m34*M2.m41,
		M1.m31*M2.m12 + M1.m32*M2.m22 + M1.m33*M2.m32 + M1.m34*M2.m42,
		M1.m31*M2.m13 + M1.m32*M2.m23 + M1.m33*M2.m33 + M1.m34*M2.m43,
		M1.m31*M2.m14 + M1.m32*M2.m24 + M1.m33*M2.m34 + M1.m34*M2.m44,
		M1.m41*M2.m11 + M1.m42*M2.m21 + M1.m43*M2.m31 + M1.m44*M2.m41,
		M1.m41*M2.m12 + M1.m42*M2.m22 + M1.m43*M2.m32 + M1.m44*M2.m42,
		M1.m41*M2.m13 + M1.m42*M2.m23 + M1.m43*M2.m33 + M1.m44*M2.m43,
		M1.m41*M2.m14 + M1.m42*M2.m24 + M1.m43*M2.m34 + M1.m44*M2.m44,
	};
}

template <class T>
vec3<T> operator*(const mat3<T>& M, const vec3<T>& v)
{
	return {
		M.m11 * v.x + M.m12 * v.y + M.m13 * v.z,
		M.m21 * v.x + M.m22 * v.y + M.m23 * v.z,
		M.m31 * v.x + M.m32 * v.y + M.m33 * v.z,
	};
}

mat4<float> LookAt(vec3<float> eye, vec3<float> at, vec3<float> up);

mat4<float> Frustum(float left, float right, float bottom, float top, float near, float far);