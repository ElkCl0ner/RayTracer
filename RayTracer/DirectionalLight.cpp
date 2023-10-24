#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Vector3& c, const Vector3& dir) : Light(c), direction(dir)
{
}
