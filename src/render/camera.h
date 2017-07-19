/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#pragma once

#include <core/vec.h>
#include <core/mat.h>


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