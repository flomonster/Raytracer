#include <vect.h>
#include <math.h>


s_vect vect_normalize(s_vect v)
{
  flt norm = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
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
