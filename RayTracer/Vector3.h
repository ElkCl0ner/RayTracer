#pragma once
class Vector3
{
public:
	double x;
	double y;
	double z;
	Vector3(double x, double y, double z);
	Vector3 operator+(Vector3& other_vector3);
	Vector3 operator-(Vector3& other_vector3);
	Vector3 operator*(double k);
	Vector3 operator/(double d);
	void normalize();
	double dot(Vector3& other_vector3);
	Vector3 operator%(Vector3& other_vector);	// cross product
	Vector3 copy();
};
