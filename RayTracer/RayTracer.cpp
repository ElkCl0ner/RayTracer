#include "Vector3.h"
#include "Sphere.h"
#include "Scene.h"
#include "Camera.h"
#include <iostream>

int main()
{
    // Create a scene
    Scene scene = Scene(1024, 768);

    // Add a camera
    Camera camera = Camera(
        Vector3(0, 0, -10),
        Vector3::Z(),
        Vector3::Y(),
        60
    );
    scene.addCamera(camera);

    // Add geometry
    Sphere ground = Sphere(
        1650,
        Vector3(23, -1700, 140),
        Vector3(.7, .7, .7)
    );
    Sphere left_sphere = Sphere(
        16.5,
        Vector3(-30, -22.5, 140),
        Vector3(0.999, 0.5, 0.5)
    );
    Sphere right_sphere = Sphere(
        16.5,
        Vector3(22, -27.5, 140),
        Vector3(0.5, 0.999, 0.5)
    );
    scene.addSphere(ground);
    scene.addSphere(left_sphere);
    scene.addSphere(right_sphere);

    // Add lights
    DirectionalLight light_top_left = DirectionalLight(
        Vector3(2, 0, 0),
        Vector3(1, 1, 0).norm()
    );
    DirectionalLight light_top_right = DirectionalLight(
        Vector3(0, 2, 0),
        Vector3(-1, 1, 0).norm()
    );
    DirectionalLight light_top = DirectionalLight(
        Vector3(2, 2, 2),
        Vector3(0, 1, 0)
    );
    scene.addDirectionalLight(light_top_left);
    scene.addDirectionalLight(light_top_right);
    scene.addDirectionalLight(light_top);

    // Render and write to output file
    Vector3* L = scene.render();

    if (!L) return 1;

    FILE* output_file;
    if (fopen_s(&output_file, "../output/out.txt", "w")) return 2;

    fprintf(output_file, "%d,%d\n", scene.width, scene.height);

    for (int i = 0; i < scene.width * scene.height; i++)
    {
        fprintf(output_file, "%f,%f,%f\n", L[i].x, L[i].y, L[i].z);
    }

    fclose(output_file);

    return 0;
}
