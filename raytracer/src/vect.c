#include <math.h>

#include "vect.h"


flt vect_norm(s_vect v)
{
  return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}


s_vect vect_normalize(s_vect v)
{
  flt norm = vect_norm(v);
  return VECT(v.x / norm, v.y / norm, v.z / norm);
}


s_vect vect_cross(s_vect a, s_vect b)
{
  return VECT(a.y * b.z - b.y * a.z,
              a.z * b.x - b.z * a.x,
              a.x * b.y - b.x * a.y);
}


s_vect vect_add(s_vect a, s_vect b)
{
  return VECT(a.x + b.x,
              a.y + b.y,
              a.z + b.z);
}


s_vect vect_sub(s_vect a, s_vect b)
{
  return VECT(a.x - b.x,
              a.y - b.y,
              a.z - b.z);
}

s_vect vect_mult(s_vect v, flt s)
{
  return VECT(v.x * s,
              v.y * s,
              v.z * s);
}


flt vect_dot(s_vect a, s_vect b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}


flt vect_dist(s_vect a, s_vect b)
{
  return vect_norm(vect_sub(b, a));
}
