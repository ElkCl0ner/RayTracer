#pragma once
#include "Vector3.h"
#include "DirectionalLight.h"
#include "Camera.h"
#include "Sphere.h"
#include <list>
class Scene
{
public:
	int width;
	int height;
	int active_camera;
	std::list<Camera> cameras;
	std::list<Sphere> spheres;
	std::list<DirectionalLight> directional_lights;
	Scene(int width, int height);
	void addCamera(Camera& camera);
	bool setActiveCamera(int i);
	void addSphere(const Sphere& sphere);
	void addDirectionalLight(DirectionalLight& light);
	Rays generateEyeRays();
	void intersect(Rays& eye_rays, double* hit_distances, Vector3* hit_normals, Sphere** hit_sphere);
	Vector3* shade(double* hit_distances, Vector3* hit_normals, Sphere** hit_sphere, int length);
	Vector3* render();
};
