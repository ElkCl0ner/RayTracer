#pragma once
#include "Vector3.h"
class Rays
{
public:
	Vector3* origins;
	Vector3* directions;
	int length;
	Rays(Vector3* origins, Vector3* directions, int length);
	void normalizeDirections();
};
