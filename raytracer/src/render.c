#include <math.h>

#include "ppm.h"
#include "ray.h"
#include "svati.h"
#include "trian.h"
#include "screen.h"


s_object *scene_intersection(s_ray *ray, s_scene *scene, s_ray *res)
{
  flt dist = -INFINITY;
  s_ray best;
  s_object *best_obj = NULL;
  for (s_object *obj = scene->objects; obj; obj = obj->next)
    for (size_t i = 0; i < obj->count; i++)
    {
      flt curdist = trian_intersect(&obj->trians[i], ray, res);
      if (curdist > dist)
      {
        dist = curdist;
        best = *res;
        best_obj = obj;
      }
    }

  *res = best;
  return best_obj;
}




s_pix ray_render(s_ray *ray, s_scene *scene)
{
  s_ray nray; // normal vector of the intersecting surface
  s_object *obj = scene_intersection(ray, scene, &nray);

  if (!obj)
    return PIX(0, 0, 0);

  // TODO: compose lights
  return color_compose(obj->material.Ka, BCOLOR(42, 0, 0));
}


s_image *scene_render(s_scene *scene)
{
  const s_camera *cam = &scene->camera;
  const s_screen scr = screen_init(cam);
  s_image *img = image_alloc(cam->width, cam->height);

  int h = cam->height;
  int w = cam->width;
  for (int y = 0; y < h; y++)
    for (int x = 0; x < w; x++)
    {
      s_ray ray = screen_raycast(&scr, cam, x, y);
      IMG_AT(img, x, y) = ray_render(&ray, scene);
    }

  return img;
}
