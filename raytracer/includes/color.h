#pragma once


#include "defs.h"


typedef struct color
{
  flt r;
  flt g;
  flt b;
} s_color;


#define COLOR(R, G, B)                          \
  ((s_color)                                    \
  {                                             \
    (R), (G), (B)                               \
  })


#define BCOLOR(R, G, B)                         \
  COLOR((R) / 255., (G) / 255., (B) / 255.)


s_color color_compose(s_color a, s_color b);
