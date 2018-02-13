#pragma once
#ifndef LIGHT_H
#define LIGHT_H
//#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
//#include "SDLauxiliary.h"
//#include "TestModelH.h"
//#include <stdint.h>
//#include "limits"
//#include "light.h"

using glm::vec3;
using glm::vec4;

struct Intersection
{
  vec4 position;
  float distance;
  int triangleIndex;
};

vec3 DirectLight( const Intersection& i, const vec4 &normal);
// test
#endif
