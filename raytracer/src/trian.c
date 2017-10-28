#include <math.h>
#include <ray.h>
#include <svati.h>

#include <stdbool.h>



static inline s_vect trian_normal(const s_trian *trian)
{
  return trian->vertices[0].vn; // TODO: interpolation
}


bool trian_intersect(const s_trian *tri, const s_ray *ray, s_ray *res)
{
  s_vect n = trian_normal(tri);
  // http://mathworld.wolfram.com/NormalVector.html
  //  n.x * x + n.y * y + n.z * z + (- n.z * z0 - n.x * x0 - n.y * y0) = 0
  s_vect A = tri->vertices[0].v;
  flt d = - n.x * A.x - n.y * A.y - n.z * A.z;

  flt denom = vect_dot(n, ray->dir);
  if (!denom)
    return false;

  flt dist = -((vect_dot(n, ray->orig) + d) / denom);

  if (dist < 0)
    return false;

  res->orig = vect_add(ray->orig, vect_mult(ray->dir, dist));
  res->dir = vect_normalize(n);
  return true;
}
