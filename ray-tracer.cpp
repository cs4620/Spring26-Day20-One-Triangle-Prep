#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
// #include <iostream>

// using namespace std;

struct Vector3
{
  float x, y, z;
  Vector3 add(Vector3 other)
  {
    return {x + other.x, y + other.y, z + other.z};
  }
  Vector3 sub(Vector3 other)
  {
    return {x - other.x, y - other.y, z - other.z};
  }
  Vector3 times(float other)
  {
    return {x * other, y * other, z * other};
  }
  float dot(Vector3 other)
  {
    return x * other.x + y * other.y + other.z * z;
  }
  Vector3 cross(Vector3 other){
    return {
      y*other.z-z*other.y,
      z*other.x-x*other.z,
      x*other.y-y*other.x,
    };
  }
  float length(){
    return sqrt(x*x+y*y+z*z);
  }
  Vector3 normalized(){
    const float l = length();
    return {x/l, y/l,z/l};
  }
};

int main()
{

  Vector3 camera_origin = {0,0,0};

  Vector3 p0 = {-1,1,-1};
  Vector3 p1 = {-1,-1,-1};
  Vector3 p2 = {1,1,-1};


  const int w = 640;
  const int h = 640;

  unsigned char pixels[w * h * 3];

  for (float y = 0; y < h; y++)
  {
    for (float x = 0; x < w; x++)
    {
      // if(x==100&&y==100){
      //   int a = 0;
      // }
      float _x = x/w*2-1;
      float _y = -(y/h*2-1);

      Vector3 target = {_x, _y, -1};
      Vector3 ray_direction = (Vector3{_x,_y,-1}.sub(camera_origin)).normalized();

      Vector3 leg1 = p1.sub(p0);
      Vector3 leg2 = p2.sub(p1);
      Vector3  normal = leg1.cross(leg2);
      float d = -normal.dot(p0);

      //Where do we hit the plane?
      float t = (-d-camera_origin.dot(normal))/(camera_origin.dot(ray_direction));
      Vector3 plane_collission = camera_origin.add(ray_direction.times(t));

      int idx = (y * w + x) * 3;
      bool white = true;
      unsigned char color = white ? 255 : 0;
      pixels[idx] = color;
      pixels[idx + 1] = color;
      pixels[idx + 2] = color;
    }
  }

  stbi_write_png("image.png", w, h, 3, pixels, w * 3);
  return 0;
}
