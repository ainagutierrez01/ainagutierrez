#pragma once

#include "framework.h"

class Light
{
public:
    Vector3 position;
    Vector3 id;
    Vector3 is;

    // Constructor
    Light(Vector3 position, Vector3 id, Vector3 is);
};