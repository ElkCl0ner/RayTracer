#include "Rays.h"

Rays::Rays(Vector3* origins, Vector3* directions, int length)
{
	this->origins = origins;
	this->directions = directions;
	this->length = length;
}

void Rays::normalizeDirections()
{
	for (Vector3* ptr = directions; ptr < directions + length; ptr++) {
		ptr->normalize();
	}
}
