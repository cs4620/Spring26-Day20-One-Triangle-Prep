#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cmath>
// #include <iostream>

// using namespace std;

int main()
{
  const int w = 640;
  const int h = 640;
  
  unsigned char pixels[w * h * 3];

  for (float y = 0; y < h; y++)
  {
    for (float x = 0; x < w; x++)
    {
      

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
