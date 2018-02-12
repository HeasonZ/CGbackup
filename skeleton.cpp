#include <iostream>
#include <glm/glm.hpp>
#include <SDL.h>
#include "SDLauxiliary.h"
#include "TestModelH.h"
#include <stdint.h>
#include "limits"
#include <omp.h>

using namespace std;
using glm::vec3;
using glm::mat3;
using glm::vec4;
using glm::mat4;

struct Intersection
{
  vec4 position;
  float distance;
  int triangleIndex;
} closestIntersection;

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 256
#define FULLSCREEN_MODE false

/* ----------------------------------------------------------------------------*/
/* FUNCTIONS                                                                   */

void Update(vec4 &cameraPos, float &yaw, mat4 &R);
void Draw(screen* screen, const vector<Triangle>& triangles, Intersection& closestIntersection, vec4 &cameraPos, mat4 &R);
bool ClosestIntersection(vec4 start,
  vec4 dir,
  const vector<Triangle>& triangles,
  Intersection& closestIntersection );

int main( int argc, char* argv[] )
{
  vector<Triangle> triangles;
  LoadTestModel( triangles );
  vec4 cameraPos( 0, 0, -2, 1.0);
  float yaw = 0.0; // store the angle of the angle.
  vec4 ()
  mat4 R;
  screen *screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN_MODE );
  int a = 0;
  while( NoQuitMessageSDL() )
    {
      // cameraPos.z = cameraPos.z + 0.01;

      Update(cameraPos, yaw, R);
      std::cout << "------------ " << a << std::endl;
      Draw(screen, triangles, closestIntersection, cameraPos, R);
      SDL_Renderframe(screen);
    }

  SDL_SaveImage( screen, "screenshot.bmp" );

  KillSDL(screen);
  return 0;
}

/*Place your drawing here*/
void Draw(screen* screen, const vector<Triangle>& triangles, Intersection& closestIntersection, vec4 &cameraPos, mat4 &R)
{
  /* Clear buffer */
  memset(screen->buffer, 0, screen->height*screen->width*sizeof(uint32_t));
  using glm::vec4;
  float focalLength = SCREEN_HEIGHT/2;
  for(int x=0; x<SCREEN_WIDTH; x++){
    for(int y=0; y<SCREEN_HEIGHT; y++){
      vec4 direction(x-SCREEN_WIDTH/2, y-SCREEN_WIDTH/2, focalLength, 1);
      direction = direction*R;
      bool validPixel = ClosestIntersection(cameraPos, direction, triangles, closestIntersection);
      if (validPixel){
        vec3 colour(triangles[closestIntersection.triangleIndex].color);
        PutPixelSDL(screen, x, y, colour);
      }
    }
  }

}

/*Place updates of parameters here*/
void Update(vec4 &cameraPos, float &yaw, mat4 &R)
{
  static int t = SDL_GetTicks();
  /* Compute frame time */
  int t2 = SDL_GetTicks();
  float dt = float(t2-t);
  t = t2;
  mat4 Rotation;
  /*Good idea to remove this*/
  std::cout << "Render time: " << dt << " ms." << std::endl;
  /* Update variables*/
  const uint8_t* keystate = SDL_GetKeyboardState( 0 );
  if( keystate[SDL_SCANCODE_UP] )
  {
    cameraPos[2] = cameraPos[2]+0.01;
  }
  if( keystate[SDL_SCANCODE_DOWN] )
  {
    cameraPos[2] = cameraPos[2]-0.01;
  }  
  if( keystate[SDL_SCANCODE_LEFT] )
  {
    yaw = yaw - 0.1;
    Rotation = mat4(cos(yaw), 0.0f, sin(yaw), 1.0f, 
      0.0f, 1.0f, 0.0f, 1.0f,
      -sin(yaw), 0.0f, cos(yaw), 1.0f,
      0.0f, 0.0f, 0.0f, 1.0f);
    R = Rotation;
  }
  if( keystate[SDL_SCANCODE_RIGHT] )
  {
    yaw = yaw + 0.1;
    Rotation = mat4(cos(yaw), 0.0f, sin(yaw),1.0f, 0.0f, 1.0f, 0.0f,1.0f, -sin(yaw), 0.0f,
                  cos(yaw),1.0f,
                  0.0f, 0.0f, 0.0f, 1.0f);
    R = Rotation;
  }  

}

bool ClosestIntersection(vec4 start,vec4 dir,const vector<Triangle>& triangles,Intersection& closestIntersection)
{
  float m = std::numeric_limits<float>::max();
  bool checkDistance = false;
  float min = m;
  for(size_t i=0; i<triangles.size(); i++){
    using glm::vec4;
    using glm::mat4;
    using glm::vec3;
    using glm::mat3;
    vec4 v0 = triangles[i].v0;
    vec4 v1 = triangles[i].v1;
    vec4 v2 = triangles[i].v2;
    vec3 e1 = vec3(v1.x-v0.x,v1.y-v0.y,v1.z-v0.z);
    vec3 e2 = vec3(v2.x-v0.x,v2.y-v0.y,v2.z-v0.z);
    vec3 b  = vec3(start.x-v0.x,start.y-v0.y,start.z-v0.z);
    vec3 d(dir[0],dir[1],dir[2]);
    mat3 A( -d, e1, e2 );
    vec3 x = glm::inverse( A ) * b;

    if((x[0]>=0)&&(x[1]>=0)&&(x[2]>=0)&&(x[1]+x[2]<=1)){
      vec4 dist = dir*x[0];
      float distance = sqrt(dist[0]*dist[0]+dist[1]*dist[1]+dist[2]*dist[2]);
      if(distance<m){
        if(distance < min){
          min = distance;
          closestIntersection.triangleIndex = i;
          closestIntersection.distance = distance;
          closestIntersection.position = start + dir*x[0];
        }
        checkDistance = true;
      }
    }
  }
  return checkDistance;
}
