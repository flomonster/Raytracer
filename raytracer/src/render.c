#include <stdbool.h>
#include <math.h>

#include "ppm.h"
#include "ray.h"
#include "screen.h"
#include "svati.h"
#include "trian.h"


s_object *scene_intersection(s_ray *ray, s_scene *scene, s_ray *res)
{
  flt dist = INFINITY;
  s_ray best;
  s_object *best_obj = NULL;
  for (s_object *obj = scene->objects; obj; obj = obj->next)
    for (size_t i = 0; i < obj->count; i++)
    {
      flt curdist = trian_intersect(&obj->trians[i], ray, res);
      if (curdist < dist)
      {
        dist = curdist;
        best = *res;
        best_obj = obj;
      }
    }

  *res = best;
  return best_obj;
}

static bool is_directional_shadow(s_vect pos, s_vect dir, s_scene *scene)
{
  s_ray ray = RAY(pos, dir);
  s_ray res;
  return !scene_intersection(&ray, scene, &res);
}

s_pix ray_render(s_ray *ray, s_scene *scene)
{
  s_ray nray; // normal vector of the intersecting surface
  s_object *obj = scene_intersection(ray, scene, &nray);

  if (!obj)
    return PIX(0, 0, 0);

  s_color color = COLOR(0, 0, 0);;

  for (size_t i = 0; i < scene->lights_count; i++)
    switch (scene->lights[i].type)
    {
      flt ld;
      s_color col;
      case AMBIENT:
        col = color_compose(scene->lights[i].color, obj->material.Ka);
        color = color_add(color, col);
      break;
      case DIRECTIONAL:
        if (is_directional_shadow(nray.orig, vect_mult(scene->lights[i].data, -1), scene))
        {
          ld = vect_dot(vect_mult(scene->lights[i].data, -1), nray.dir);
          col = color_compose(scene->lights[i].color, obj->material.Kd);
          color = color_add(color, color_mult(col, ld));
        }
      break;
      case POINT:
        ld = 1 / vect_dist(scene->lights[i].data, nray.orig);
        ld *= vect_dot(nray.dir, vect_normalize(vect_sub(scene->lights[i].data,
                                                         nray.orig)));
        col = color_compose(scene->lights[i].color, obj->material.Kd);
        color = color_add(color, color_mult(col, ld));
      break;
    }

  return color;
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
