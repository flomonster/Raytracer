#include <math.h>
#include <ray.h>
#include <svati.h>

#include <stdbool.h>



static inline s_vect trian_normal(const s_trian *trian)
{
  return trian->vertices[0].vn; // TODO: interpolation
}


static inline bool is_in_triangle(const s_trian *tri, const s_vect *pt)
{
  /* https://math.stackexchange.com/questions/4322/
  **  check-whether-a-point-is-within-a-3d-triangle
  */
  const s_vect a = tri->vertices[0].v;
  const s_vect b = tri->vertices[1].v;
  const s_vect c = tri->vertices[2].v;

  flt ab = vect_dist(a, b);
  flt ac = vect_dist(a, c);
  flt pa = vect_dist(*pt, a);
  flt pb = vect_dist(*pt, b);
  flt pc = vect_dist(*pt, c);

  // two times the area of the triangle
  flt area2 = ab * ac;
  flt alpha = pb * pc / area2;
  flt beta = pc * pa / area2;
  flt gamma = 1. - alpha - beta;
#define CRIT(K) (0. <= (K) && (K) <= 1.)
  return CRIT(alpha) && CRIT(beta) && CRIT(gamma);
#undef CRIT
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

  // distance between the ray source and plane intersection
  flt dist = -((vect_dot(n, ray->orig) + d) / denom);

  if (dist < 0)
    return false;

  res->orig = vect_add(ray->orig, vect_mult(ray->dir, dist));
  if (!is_in_triangle(tri, &res->orig))
    return false;

  res->dir = vect_normalize(n);
  return true;
}
