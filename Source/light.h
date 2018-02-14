#pragma once
#ifndef LIGHT_H
#define LIGHT_H

// #include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include <vector>
//#include "SDLauxiliary.h"
// #include "TestModelH.h"
// #include <stdint.h>
//#include "limits"

#define pi 3.1415926
using glm::vec3;
using glm::vec4;
using std::vector;

struct Intersection
{
  vec4 position;
  float distance;
  int triangleIndex;
};


#endif
