#include "svati.h"


void vect_print(s_vect *v)
{
  printf("%f %f %f\n", v->x, v->y, v->z);
}

void color_print(s_color *v)
{
  printf("%f %f %f\n", v->r, v->g, v->b);
}

void camera_print(struct camera *cam)
{
  printf("%zu %zu %f\n", cam->width, cam->height, cam->fov);
  vect_print(&cam->pos);
  vect_print(&cam->u);
  vect_print(&cam->v);
}

void light_print(struct light *l)
{
  printf("%d\n", l->type);
  color_print(&l->color);
  if (l->type != AMBIENT)
    vect_print(&l->data);
}

void vertex_print(struct vertex *v)
{
  vect_print(&v->v);
  vect_print(&v->vn);
}


void trian_print(struct trian *t)
{
  printf("trian\n");
  for (int i = 0; i < 3; i++)
    vertex_print(&t->vertices[i]);
}

void object_print(struct object *o)
{
  if (!o)
    return;

  printf("object: %zu\n", o->count);
  for (size_t i = 0; i < o->count; i++)
    trian_print(&o->trians[i]);
  object_print(o->next);
}

void scene_print(struct scene *s)
{
  camera_print(&s->camera);
  for (size_t i = 0; i < s->lights_count; i++)
    light_print(s->lights + i);
  object_print(s->objects);
}
