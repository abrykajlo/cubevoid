#pragma once

#include <cmath>

template <class T>
struct vec2
{
	T x;
	T y;
};

template <class T>
struct vec3
{
	T x;
	T y;
	T z;
};

template <class T>
struct vec4
{
	T x;
	T y;
	T z;
	T w;
};

//-------------------------------------------------------------------
// Operators for vec3
//-------------------------------------------------------------------
template <class T>
vec3<T> operator/(const vec3<T>& v, T x)
{
	return { v.x / x, v.y / x, v.z / x };
}

template <class VecT>
VecT normalize(const VecT& v)
{
	return v / sqrt(dot(v, v));
}

template <class T>
T dot(const vec3<T>& v1, const vec3<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <class T>
vec3<T> cross(const vec3<T>& v1, const vec3<T>& v2)
{
	return {
		v1.y * v2.z - v1.z * v2.y, 
		v1.z * v2.x - v1.x * v2.z, 
		v1.x * v2.y - v1.y * v2.x 
	};
}

template <class T>
vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2)
{
	return { 
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z 
	};
}