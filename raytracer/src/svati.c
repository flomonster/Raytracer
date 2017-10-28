#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <svati.h>

static void scene_lights_expand(s_scene *scene)
{
  scene->lights = realloc(scene->lights,
                          sizeof (s_light) * (scene->lights_count + 10));
  if (!scene->lights)
    err(1, "svati.c/scene_lights_expand: realloc failed");
}

static void camera_parse(s_scene *scene, FILE *fin)
{
  s_camera *cam = &scene->camera;
  if (fscanf(fin, "%zu %zu %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
             &cam->width, &cam->height, &cam->pos.x, &cam->pos.y, &cam->pos.z,
             &cam->u.x, &cam->u.y, &cam->u.z, &cam->v.x, &cam->v.y, &cam->v.z,
             &cam->fov) != 12)
    err(2, "svati/scene_parse: error parsing camera");
}

static void ambiant_light_parse(s_scene *scene, FILE *fin)
{
  if (scene->lights_count % 10 == 0)
    scene_lights_expand(scene);

  s_light *new_light = &scene->lights[scene->lights_count++];

  new_light->type = AMBIANT;
  new_light->data = VECT(0, 0, 0);

  if (fscanf(fin, "%lf %lf %lf", &new_light->color.r, &new_light->color.g,
             &new_light->color.b) != 3)
    err(2, "svati/ambiant_light_parse: error parsing ambiant light");
}

static void point_light_parse(s_scene *scene, FILE *fin)
{
  if (scene->lights_count % 10 == 0)
    scene_lights_expand(scene);

  s_light *new_light = &scene->lights[scene->lights_count++];

  new_light->type = POINT;

  if (fscanf(fin, "%lf %lf %lf %lf %lf %lf",
             &new_light->color.r, &new_light->color.g, &new_light->color.b,
             &new_light->data.x, &new_light->data.y, &new_light->data.z) != 6)
    err(2, "svati/point_light_parse: error parsing point light");
}

static void directional_light_parse(s_scene *scene, FILE *fin)
{
  if (scene->lights_count % 10 == 0)
    scene_lights_expand(scene);

  s_light *new_light = &scene->lights[scene->lights_count++];

  new_light->type = DIRECTIONAL;

  if (fscanf(fin, "%lf %lf %lf %lf %lf %lf",
             &new_light->color.r, &new_light->color.g, &new_light->color.b,
             &new_light->data.x, &new_light->data.y, &new_light->data.z) != 6)
    err(2, "svati/directional_light_parse: error parsing directional light");
}

static void object_parse(s_scene *scene, FILE *fin)
{
  size_t count = 0;
  if (fscanf(fin, "%zu", &count) != 1)
  err(2, "svati/object_parse: error parsing object");

  s_object *new_object = malloc(sizeof (s_object) + count * sizeof (s_trian));

  *new_object = (s_object)
  {
    count,
    DEFAULT_MATERIAL,
    scene->objects
  };

  char name[3];
  size_t v_count = 0;
  size_t vn_count = 0;
  while ((v_count * 3 != new_object->count || vn_count * 3 != new_object->count)
         &&fscanf(fin, "%2s", name) == 1)
  {
    if (!strcmp(name, "Ka"))
    {
      if (fscanf(fin, "%lf %lf %lf", &new_object->material.Ka.r,
                 &new_object->material.Ka.g, &new_object->material.Ka.b) != 3)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "Kd"))
    {
      if (fscanf(fin, "%lf %lf %lf", &new_object->material.Kd.r,
                 &new_object->material.Kd.g, &new_object->material.Kd.b) != 3)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "Ks"))
    {
      if (fscanf(fin, "%lf %lf %lf", &new_object->material.Ks.r,
                 &new_object->material.Ks.g, &new_object->material.Ks.b) != 3)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "Ns"))
    {
      if (fscanf(fin, "%lf", &new_object->material.Ns) != 1)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "Nr"))
    {
      if (fscanf(fin, "%lf", &new_object->material.Nr) != 1)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "Ni"))
    {
      if (fscanf(fin, "%lf", &new_object->material.Ni) != 1)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "d"))
    {
      if (fscanf(fin, "%lf", &new_object->material.d) != 1)
        err(2, "svati/object_parse: error parsing object");
    }

    else if (!strcmp(name, "v"))
    {
      s_trian *t = &new_object->trians[v_count];
      if (fscanf(fin, "%lf %lf %lf %*s %lf %lf %lf %*s %lf %lf %lf",
                 &t->vertices[0].v.x, &t->vertices[0].v.y, &t->vertices[0].v.z,
                 &t->vertices[1].v.x, &t->vertices[1].v.y, &t->vertices[1].v.z,
                 &t->vertices[2].v.x, &t->vertices[2].v.y, &t->vertices[2].v.z)
          != 9)
        err(2, "svati/object_parse: error parsing object");
      v_count++;
    }

    else if (!strcmp(name, "vn"))
    {
      s_trian *t = &new_object->trians[vn_count];
      if (fscanf(fin, "%lf %lf %lf %*s %lf %lf %lf %*s %lf %lf %lf",
                 &t->vertices[0].vn.x, &t->vertices[0].vn.y, &t->vertices[0].vn.z,
                 &t->vertices[1].vn.x, &t->vertices[1].vn.y, &t->vertices[1].vn.z,
                 &t->vertices[2].vn.x, &t->vertices[2].vn.y, &t->vertices[2].vn.z)
          != 9)
        err(2, "svati/object_parse: error parsing object");
      vn_count++;
    }

    else if (!strcmp(name, "#"))
    {
      if (fscanf(fin, "%*[^\n]") != 0)
        err(2, "svati/scene_parse: error parsing object");
    }

    else
      err(2, "svati/object_parse: error parsing object");
  }
  scene->objects = new_object;
}

s_scene *scene_parse(FILE *fin)
{
  s_scene *scene = malloc(sizeof (*scene));
  if (!scene)
    err(1, "svati.c/scene_parse: malloc failed");

  scene->lights_count = 0;
  scene->lights = malloc(sizeof (s_light) * 10);
  if (!scene->lights)
    err(1, "svati.c/scene_parse: malloc failed");

  scene->objects = NULL;

  char name[8];
  while (fscanf(fin, "%7s", name) == 1)
  {
    if (!strcmp(name, "camera"))
      camera_parse(scene, fin);

    else if (!strcmp(name, "a_light"))
      ambiant_light_parse(scene, fin);

    else if (!strcmp(name, "p_light"))
      point_light_parse(scene, fin);

    else if (!strcmp(name, "d_light"))
      directional_light_parse(scene, fin);

    else if (!strcmp(name, "object"))
      object_parse(scene, fin);

    else if (!strcmp(name, "#"))
    {
      if (fscanf(fin, "%*[^\n]") != 0)
        err(2, "svati/scene_parse: error parsing scene");
    }

    else
      err(2, "svati/scene_parse: error parsing scene");
  }
  return scene;
}

void scene_destroy(s_scene *scene)
{
  free(scene->lights);
  while (scene->objects)
  {
    s_object *obj = scene->objects;
    scene->objects = scene->objects->next;
    free(obj);
  }
  free(scene);
}
