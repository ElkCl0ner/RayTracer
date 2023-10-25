#define _USE_MATH_DEFINES

#include "Scene.h"
#include <cmath>
#include "DirectionalLight.h"

Scene::Scene(int width, int height)
{
	this->width = width;
	this->height = height;
	active_camera = -1;
}

void Scene::addCamera(Camera& camera)
{
	cameras.push_back(camera);
}

bool Scene::setActiveCamera(int i)
{
	if (0 > i >= cameras.size()) {
		return false;
	}
	active_camera = i;
	return true;
}

void Scene::addSphere(const Sphere& sphere)
{
	spheres.push_back(sphere);
}

void Scene::addDirectionalLight(DirectionalLight& light)
{
	directional_lights.push_back(light);
}

Rays Scene::generateEyeRays()
{
	int length = width * height;
	Vector3* origins = (Vector3*)malloc(length * sizeof(Vector3));
	Vector3* directions = (Vector3*)malloc(length * sizeof(Vector3));
	if (!origins || !directions) return Rays(nullptr, nullptr, 0);

	// Populate origins
	Vector3 origin = cameras.begin().operator++(active_camera)->position.copy();
	for (int i = 0; i < length; i++) {
		origins[i] = origin.copy();
	}

	// Compute directions
	double x_step = 2. / width;
	double y_step = 2. / height;

	double y_scale = tan(cameras.begin().operator++(active_camera)->fov * M_PI / 180);
	double x_scale = y_scale * width / height;

	Vector3 direction_up = cameras.begin().operator++(active_camera)->up.copy();
	Vector3 direction_right = cameras.begin().operator++(active_camera)->direction % direction_up;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double x_ndc = -1. + (x + .5) * x_step;
			double y_ndc = 1. - (y + .5) * y_step;
			x_ndc *= x_scale;
			y_ndc *= y_scale;

			Vector3 at = cameras.begin().operator++(active_camera)->direction.copy();
			Vector3 displacement_x = direction_right * x_ndc;
			Vector3 displacement_y = direction_up * y_ndc;
			Vector3 ray = at + displacement_x + displacement_y;
			ray.normalize();

			directions[y * width + x] = ray;
		}
	}

	return Rays(origins, directions, length);
}

/**
* double* hit_distances should be malloc'ed and initialized with -1's
* Vector3* hit_normals should be malloc'ed and initialized with Vector3(0, 0, 0)'s
* Sphere** hit_sphere should be malloc'ed and initialized with nullptr's
*/
void Scene::intersect(Rays& eye_rays, double* hit_distances, Vector3* hit_normals, Sphere** hit_sphere)
{
	for (Sphere& current_sphere : spheres) {
		double* new_hit_distances = current_sphere.intersect(eye_rays);

		for (int i = 0; i < eye_rays.length; i++) {
			if (new_hit_distances[i] != -1 && (hit_distances[i] == -1 || new_hit_distances[i] < hit_distances[i])) {
				hit_distances[i] = new_hit_distances[i];
				hit_normals[i] = eye_rays.directions[i] * new_hit_distances[i];
				hit_normals[i] = hit_normals[i] + eye_rays.origins[i];
				hit_normals[i] = hit_normals[i] - current_sphere.center;
				hit_normals[i].normalize();
				hit_sphere[i] = &current_sphere;
			}
		}
	}
}

Vector3* Scene::shade(double* hit_distances, Vector3* hit_normals, Sphere** hit_sphere, int length)
{
	Vector3* L = (Vector3*)malloc(length * sizeof(Vector3));
	if (!L) return nullptr;
	for (int i = 0; i < length; i++) {
		L[i] = Vector3(0., 0., 0.);
	}

	for (DirectionalLight& directional_light : directional_lights) {
		Vector3 direction_towards_light = directional_light.direction * -1;
		for (int i = 0; i < length; i++) {
			if (!hit_sphere[i]) continue;
			Vector3 temp = hit_sphere[i]->brdf / M_PI;
			temp.x *= directional_light.color.x;
			temp.y *= directional_light.color.y;
			temp.z *= directional_light.color.z;
			temp = temp * std::max(0., hit_normals[i].dot(direction_towards_light));
			L[i] = L[i] + temp;
		}
	}

	return L;
}

Vector3* Scene::render()
{
	// Generate eye rays
	Rays eye_rays = generateEyeRays();

	// Intersect eye rays
	int length = eye_rays.length;
	
	double* hit_distances = (double*)malloc(length * sizeof(double));
	Vector3* hit_normals = (Vector3*)malloc(length * sizeof(Vector3));
	Sphere** hit_sphere = (Sphere**)malloc(length * sizeof(Vector3*));

	if (!hit_distances || !hit_normals || !hit_sphere) return nullptr;

	for (int i = 0; i < length; i++) {
		hit_distances[i] = -1;
		hit_normals[i] = Vector3(0., 0., 0.);
		hit_sphere[i] = nullptr;
	}

	intersect(eye_rays, hit_distances, hit_normals, hit_sphere);

	// Shade hit points
	return shade(hit_distances, hit_normals, hit_sphere, length);
}
