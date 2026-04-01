#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
#include <iostream>

using namespace std;

struct Vector3
{
  float x, y, z;
  Vector3 add(Vector3 b)
  {
    return {x + b.x, y + b.y, z + b.z};
  }
  Vector3 sub(Vector3 b)
  {
    return {x - b.x, y - b.y, z - b.z};
  }
  Vector3 scale(float s)
  {
    return {x * s, y * s, z * s};
  }
  float dot(Vector3 b)
  {
    return x * b.x + y * b.y + z * b.z;
  }
  Vector3 cross(Vector3 b)
  {
    return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - b.x * y};
  }
  float length()
  {
    return sqrt(x * x + y * y + z * z);
  }
  Vector3 normalize()
  {
    return {x / length(), y / length(), z / length()};
  }
  bool inTriangle(Vector3 p0, Vector3 p1, Vector3 p2)
  {
    return p0.sub(*this).cross(p0.sub(p1)).z >= 0 &&
           p1.sub(*this).cross(p1.sub(p2)).z >= 0 &&
           p2.sub(*this).cross(p2.sub(p0)).z >= 0;
  }
};





int main()
{

  int w, h;
  w = h = 640;

  Vector3 p0 = {-1, -1, -1};
  Vector3 p1 = {-1, 1, -1};
  Vector3 p2 = {1, 1, -1};


  const int tileSize = 32;
  unsigned char pixels[w * h * 3];

  for (float y = 0; y < h; y++)
  {
    for (float x = 0; x < w; x++)
    {
      if(x==w-1&&y==h-1){
        cout<<"Stop"<<endl;
      }
      float tempX = x/w * 2 -1;
      float tempY = -1 * (y/h*2-1);
      Vector3 target = {tempX, tempY, -1};
      Vector3 o = {0,0,0};
      Vector3 r = target.sub(o).normalize();

      Vector3 n = {0,0,1};
      float d = -n.dot(p0);
      float t = (-d-n.dot(o))/n.dot(r);
      Vector3 p = o.add(r.scale(t));

      int idx = (y * w + x) * 3;
      bool white = p.inTriangle(p0, p1, p2);
      unsigned char color = white ? 255 : 0;
      pixels[idx] = color;
      pixels[idx + 1] = color;
      pixels[idx + 2] = color;
    }
  }

  stbi_write_png("checkerboard.png", w, h, 3, pixels, w * 3);
  return 0;
}
