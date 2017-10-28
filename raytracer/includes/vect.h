#pragma once


#include "defs.h"


typedef struct vect3
{
  flt x;
  flt y;
  flt z;
} s_vect3;


#define VECT(X, Y, Z)                           \
  ((s_vect)                                     \
  {                                             \
    (X), (Y), (Z)                               \
  })

typedef s_vect3 s_vect;


s_vect vect_normalize(s_vect v);
s_vect vect_cross(s_vect a, s_vect b);
s_vect vect_add(s_vect a, s_vect b);
s_vect vect_sub(s_vect a, s_vect b);
s_vect vect_mult(s_vect v, flt s);
flt vect_dot(s_vect a, s_vect b);
flt vect_norm(s_vect v);
flt vect_dist(s_vect a, s_vect b);
