#include <iostream>
#include "Vector3.h"
#include "Rays.h"
#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    Vector3 v = Vector3(1., 2., 3.);
    Sphere s = Sphere(
        Vector3(0.,0.,0.),
        1.,
        Vector3(.9,.9,.9)
    );
    const int length = 6;
    Vector3 origins[length] = {
        Vector3(0.,2.,-2.),
        Vector3(0.,1.,-2.),
        Vector3(0.,0.,-2.),
        Vector3(0.,-1.,-2.),
        Vector3(0.,-2.,-2.),
        Vector3(0.,-4.,-2.)
    };
    Vector3 directions[length] = {
        Vector3(0.,0.,1.),
        Vector3(0.,0.,1.),
        Vector3(0.,0.,1.),
        Vector3(0.,0.,1.),
        Vector3(0.,0.,1.),
        Vector3(0.,0.,1.)
    };
    Rays r = Rays(
        origins,
        directions,
        length
    );
    r.normalizeDirections();
    printf("Vector3: (%f, %f, %f)\n", v.x, v.y, v.z);
    printf("Sphere:\n- pos: (%f, %f, %f)\n- radius: %f\n- brdf: (%f, %f, %f)\n",
        s.center.x, s.center.y, s.center.z,
        s.radius,
        s.brdf.x, s.brdf.y, s.brdf.z
    );
    std::cout << "Sphere Intersection:" << std::endl;
    double* hit_distances = s.intersect(r);
    if (!hit_distances) {
        printf("hit_distances is null\n");
        return 0;
    }
    for (int i = 0; i < length; i++) {
        printf("Ray(%f, %f, %f), t=%f\n",
            origins[i].x, origins[i].y, origins[i].z,
            hit_distances[i]
        );
    }

    Camera camera = Camera(
        Vector3(0, 0, 0),
        Vector3(0, 0, 1),
        Vector3(0, 1, 0),
        60
    );
    Scene scene = Scene(
        16, 9, camera
    );
    Rays eye_rays = scene.generateEyeRays();
    for (int i = 0; i < eye_rays.length; i++) {
        printf("(%f, %f, %f) (%f, %f, %f)\n",
            eye_rays.origins[i].x, eye_rays.origins[i].y, eye_rays.origins[i].z,
            eye_rays.directions[i].x, eye_rays.directions[i].y, eye_rays.directions[i].z
        );
    }

    return 0;
}
