#include <math.h>

#include "screen.h"
#include "vect.h"
#include "ray.h"


s_screen screen_init(const s_camera *cam)
{
  s_screen ret;
  ret.w = vect_mult(vect_cross(cam->u, cam->v), -1);
  ret.L = cam->width / (2. * tan(cam->fov / 2.));
  ret.C = vect_add(cam->pos, vect_mult(ret.w, ret.L));
  return ret;
}


s_ray screen_raycast(const s_screen *scr, const s_camera *cam,
                     int x, int y)
{
  int half_cam = cam->width / 2;
  s_vect pu = vect_mult(cam->u, (x - half_cam));
  s_vect pv = vect_mult(cam->v, (y - half_cam));
  s_vect screen_point = vect_add(vect_add(scr->C, pu), pv);
  return RAY(cam->pos, vect_normalize(vect_sub(screen_point, cam->pos)));
}
