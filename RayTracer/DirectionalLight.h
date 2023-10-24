#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
public:
    Vector3 direction;
    DirectionalLight(const Vector3& color, const Vector3& dir);
};
