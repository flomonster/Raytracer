#pragma once


#include <vect.h>


typedef struct ray
{
  s_vect orig;
  s_vect dir;
} s_ray;


#define RAY(Orig, Dir)                          \
  ((s_ray)                                      \
  {                                             \
    (Orig), (Dir)                               \
  })
