#pragma once

#include "vec.hpp"
#include "mat.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	mat4<float> ViewProjection();
	
	vec3<float> eye;
	vec3<float> up;
	vec3<float> at;

private:
	mat4<float> projection_;
};