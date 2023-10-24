#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Vector3& c, double radius, const Vector3& b) : center(c), brdf(b)
{
	this->radius = radius;
}

double* Sphere::intersect(Rays& rays)
{
	double* intersect_distances = (double*) malloc(rays.length * sizeof(double));
	if (!intersect_distances) return nullptr;
	for (int i = 0; i < rays.length; i++) {
		double A = pow(rays.directions[i].x, 2) + pow(rays.directions[i].y, 2) + pow(rays.directions[i].z, 2);
		double B = 2 * (rays.directions[i].x * (rays.origins[i].x - center.x) + rays.directions[i].y * (rays.origins[i].y - center.y) + rays.directions[i].z * (rays.origins[i].z - center.z));
		double C = pow(rays.origins[i].x - center.x, 2) + pow(rays.origins[i].y - center.y, 2) + pow(rays.origins[i].z - center.z, 2) - pow(radius, 2);
		double discriminant = B * B - 4 * A * C;

		if (discriminant < 0) {
			intersect_distances[i] = -1;
		}
		else if (discriminant == 0) {
			double t = -B / (2 * A);
			intersect_distances[i] = (t > HIT_DISTANCE_THRESHOLD) ? t : -1;
		}
		else {
			double t1 = (-B - sqrt(discriminant)) / (2 * A);
			double t2 = (-B + sqrt(discriminant)) / (2 * A);
			intersect_distances[i] = (t1 > HIT_DISTANCE_THRESHOLD) ? (t1) : ((t2 > HIT_DISTANCE_THRESHOLD) ? t2 : -1);
		}
	}
	return intersect_distances;
}
