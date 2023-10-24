#pragma once
#include "Vector3.h"
#include "Rays.h"
class Geometry
{
public:
	virtual double* intersect(Rays& rays) = 0;
};
