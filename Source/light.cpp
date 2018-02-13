#include <iostream>

#include <glm/glm.hpp>
#include <SDL.h>
//#include "SDLauxiliary.h"
//#include "TestModelH.h"
//#include <stdint.h>
//#include "limits"
#include "light.h"
#include <numeric>
#include <iterator>

#define pi 3.1415926 
using namespace std;
using glm::vec3;
using glm::mat3;
using glm::vec4;
using glm::mat4;

// vec4 lightPos( 0, -0.5, -0.7, 1.0 );
vec3 lightColor = 14.f * vec3( 1, 1, 1 ); // It's the power of the light.

vec3 DirectLight(const Intersection &i, const vec4 &normal, vec4 &lightPosition){
   vec4 distance(lightPosition - i.position);
   float r = sqrt(distance[0]*distance[0]+distance[1]*distance[1]+distance[2]*distance[2]);
   vec4 unit = vec4(distance[0]/r,distance[1]/r,distance[2]/r,distance[3]/r);
   vec3 B = vec3(lightColor[0]/(4*pi*(r*r)),lightColor[1]/(4*pi*(r*r)),lightColor[2]/(4*pi*(r*r)));
   float product = glm::dot(unit, normal);
   vec3 D;
   if(product > 0){
      // std::cout << "------hahah------ " << std::endl;
      D = vec3(B[0]*product,B[1]*product,B[2]*product);
   }
   else{
      D = vec3(B[0]*0,B[1]*0,B[2]*0);
   }
   return D;
   
}


