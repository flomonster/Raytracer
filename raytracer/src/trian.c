#include <math.h>
#include <stdbool.h>

#include "ray.h"
#include "svati.h"


static inline s_vect trian_normal(const s_trian *trian)
{
  return trian->vertices[0].vn; // TODO: interpolation
}


bool same_side(s_vect p1, s_vect p2, s_vect a, s_vect b)
{
  s_vect cp1 = vect_cross(vect_sub(b, a), vect_sub(p1, a));
  s_vect cp2 = vect_cross(vect_sub(b, a), vect_sub(p2, a));
  return vect_dot(cp1, cp2) >= 0;
}


bool point_in_triangle(s_vect p, s_vect a, s_vect b, s_vect c)
{
  return (same_side(p, a, b, c)
         && same_side(p, b, a, c)
         && same_side(p, c, a, b));
}


flt trian_intersect(const s_trian *tri, const s_ray *ray,
                    s_ray *res)
{
  s_vect n = trian_normal(tri);
  // http://mathworld.wolfram.com/NormalVector.html
  //  n.x * x + n.y * y + n.z * z + (- n.z * z0 - n.x * x0 - n.y * y0) = 0
  s_vect A = tri->vertices[0].v;
  s_vect B = tri->vertices[1].v;
  s_vect C = tri->vertices[2].v;

  flt d = - n.x * A.x - n.y * A.y - n.z * A.z;

  flt denom = vect_dot(n, ray->dir);
  if (!denom)
    return INFINITY;

  // distance between the ray source and plane intersection
  flt dist = -((vect_dot(n, ray->orig) + d) / denom);

  if (dist < 0)
    return INFINITY;

  res->orig = vect_add(ray->orig, vect_mult(ray->dir, dist));
  if (!point_in_triangle(res->orig, A, B, C))
    return INFINITY;

  res->dir = vect_normalize(n);
  return dist;
}
