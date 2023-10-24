#include "Vector3.h"
#include <cmath>

Vector3::Vector3(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator+(Vector3& other_vector) {
	return Vector3(x + other_vector.x, y + other_vector.y, z + other_vector.z);
}

Vector3 Vector3::operator-(Vector3& other_vector3)
{
	return Vector3(x - other_vector3.x, y - other_vector3.y, z - other_vector3.z);
}

Vector3 Vector3::operator*(double k)
{
	return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator/(double d)
{
	return Vector3(x / d, y / d, z / d);
}

void Vector3::normalize()
{
	double magnitude = sqrt(x * x + y * y + z * z);
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

double Vector3::dot(Vector3& other_vector3)
{
	return x * other_vector3.x + y + other_vector3.y + z * other_vector3.z;
}

Vector3 Vector3::operator%(Vector3& other_vector3)
{
	return Vector3(y * other_vector3.z - z * other_vector3.y, z * other_vector3.x - x * other_vector3.z, x * other_vector3.y - y * other_vector3.x);
}

Vector3 Vector3::copy()
{
	return Vector3(x, y, z);
}
