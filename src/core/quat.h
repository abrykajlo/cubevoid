#pragma once

#include <core/vec.h>

struct quat
{
	float i;
	float j;
	float k;
	float real;

	quat(float i, float j, float k, float real);
	quat(vec3<float>& v);
	quat(vec4<float>& v);

	//returns w = real
	vec4<float> ToVec4();

	//Truncates real value and returns {i,j,k}
	vec3<float> ToVec3();
	quat Conjugate();
	quat Inverse();
};

quat operator*(quat& q1, quat& q2);
quat quat_rotation(float theta, float ux, float uy, float uz);
quat quat_rotation(float theta, vec3<float>& axis);
//TODO: add euler angle conversion functions