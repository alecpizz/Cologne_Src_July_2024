#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include "stb_image.h"

inline glm::vec3 RainbowColor(float time)
{
     const float PI = 3.14159265f;
     float hue = fmodf(time, PI * 2.0f) / (PI * 2.0f);

     float r, g, b;

     switch (int(floorf(hue * 6.0f)))
     {
     case 0:
          r = 1.0f;
          g = sinf(hue * PI);
          b = 0.0f;
          break;
     case 1:
          r = cosf(hue * PI);
          g = 1.0f;
          b = 0.0f;
          break;
     case 2:
          r = 0.0f;
          g = 1.0f;
          b = sinf(hue * PI - PI / 3.0f);
          break;
     case 3:
          r = 0.0f;
          g = cosf(hue * PI - PI / 3.0f);
          b = 1.0f;
          break;
     case 4:
          r = sinf(hue * PI - PI * 2.0f / 3.0f);
          g = 0.0f;
          b = 1.0f;
          break;
     default:
          r = 1.0f;
          g = 0.0f;
          b = 0.0f;
          break;
     }
     return glm::vec3(r, g, b);
}
#endif
