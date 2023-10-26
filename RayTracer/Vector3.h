#pragma once
#include <string>
class Vector3
{
public:
	double x;
	double y;
	double z;
	Vector3(double x, double y, double z);
	static Vector3 ZERO();
	static Vector3 X();
	static Vector3 Y();
	static Vector3 Z();
	Vector3 operator+(Vector3& other_vector3);
	Vector3 operator-(Vector3& other_vector3);
	Vector3 operator*(double k);
	Vector3 operator/(double d);
	void normalize();
	Vector3 norm();
	double dot(Vector3& other_vector3);
	Vector3 operator%(Vector3& other_vector);	// cross product
	Vector3 copy();
};
