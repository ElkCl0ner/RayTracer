#pragma once
#include "Geometry.h"
#include "Vector3.h"
class Sphere :
    public Geometry
{
public:
    const double HIT_DISTANCE_THRESHOLD = 1e-6;
    Vector3 center;
    double radius;
    Vector3 brdf;
    Sphere(double radius, const Vector3& center, const Vector3& brdf);
    double* intersect(Rays& rays) override;
};
