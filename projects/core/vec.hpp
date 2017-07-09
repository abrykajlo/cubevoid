#pragma once

template <class T, int n>
struct vec;

template <class T>
struct vec<T, 2>
{
	T x;
	T y;
};

template <class T>
struct vec<T, 3>
{
	T x;
	T y;
	T z;
};

template <class T>
struct vec<T, 4>
{
	T x;
	T y;
	T z;
	T w;
};

template <class T>
using vec2 = vec<T, 2>;

template <class T>
using vec3 = vec<T, 3>;

template <class T>
using vec4 = vec<T, 4>;