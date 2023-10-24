#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3& color, Vector3& dir) : Light(color), direction(dir)
{
}
