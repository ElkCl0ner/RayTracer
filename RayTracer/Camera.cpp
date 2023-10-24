#include "Camera.h"

Camera::Camera(const Vector3& pos, const Vector3& dir, const Vector3& up_vec, int fov) : position(pos), direction(dir), up(up_vec)
{
	this->fov = fov;
}
