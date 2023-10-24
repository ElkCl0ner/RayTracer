#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
public:
    Vector3 direction;
    DirectionalLight(Vector3& color, Vector3& dir);
};
