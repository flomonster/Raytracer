#include <math.h>
#include <stdbool.h>

#include "ray.h"
#include "svati.h"
#include "defs.h"



static inline flt same_side(s_vect N, s_vect P, s_vect A, s_vect B)
{
  s_vect edge = vect_sub(B, A);
  s_vect vp = vect_sub(P, A);
  s_vect C = vect_cross(edge, vp);
  return vect_dot(N, C);
}


flt trian_intersect(const s_trian *tri, const s_ray *ray,
                    s_ray *res)
{
  s_vect A = tri->vertices[0].v;
  s_vect B = tri->vertices[1].v;
  s_vect C = tri->vertices[2].v;

  s_vect N = vect_normalize(vect_cross(vect_sub(A, B), vect_sub(A, C)));

  // flt denom = vect_dot(N, N);


  flt ray_dot_angle = vect_dot(N, ray->dir);
  if (fabs(ray_dot_angle) < EPSILON)
    return INFINITY;

  flt d = -vect_dot(N, A);
  flt t = -(vect_dot(N, ray->orig) + d) / ray_dot_angle;
  if (t < EPSILON)
    return INFINITY;

  s_vect P = vect_add(ray->orig, vect_mult(ray->dir, t));

  if (same_side(N, P, A, B) < -EPSILON)
    return INFINITY;

  if (same_side(N, P, B, C) < -EPSILON)
    return INFINITY;

  if (same_side(N, P, C, A) < -EPSILON)
    return INFINITY;

  /* s_vect nA = tri->vertices[0].vn; */
  /* s_vect nB = tri->vertices[1].vn; */
  /* s_vect nC = tri->vertices[2].vn; */

  /* res->dir = vect_normalize(vect_add(vect_mult(nA, da), */
  /*                                    vect_add(vect_mult(nC, dc), */
  /*                                             vect_mult(nB, db)))); */
  res->dir = vect_normalize(N);
  return t;
}
