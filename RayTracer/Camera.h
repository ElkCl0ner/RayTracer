#pragma once
#include "Vector3.h"
class Camera
{
public:
	Vector3 position;
	Vector3 direction;
	Vector3 up;
	int fov;
	Camera(const Vector3& position, const Vector3& direction, const Vector3& up, int fov);
};
