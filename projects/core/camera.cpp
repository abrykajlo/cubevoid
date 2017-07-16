#include "camera.hpp"

Camera::Camera()
{
	eye = { 0, 1, 1 };
	at = { 0, 0, 0 };
	up = { 0, 1, 0 };

	projection_ = {
		0.1f, 0, 0, 0,
		0, 0.1f, 0, 0,
		0, 0, 0.1f, 0,
		0, 0, 0, 1
	};
}

Camera::~Camera()
{
}

mat4<float> Camera::ViewProjection()
{
	return projection_ * LookAt(eye, at, up);
}
