#pragma once

#include <stddef.h>


typedef double flt;

typedef struct vect3
{
  flt x;
  flt y;
  flt z;
} s_vect3;


#define VECT(X, Y, Z)                           \
  ((s_vect)                                     \
  {                                             \
    (X), (Y), (Z)                               \
  })


typedef s_vect3 s_vect;


typedef struct camera
{
  size_t width;
  size_t height;
  s_vect pos;
  s_vect u;
  s_vect v;
  flt fov;
} s_camera;


typedef struct color
{
  flt r;
  flt g;
  flt b;
} s_color;


#define COLOR(R, G, B)                          \
  ((s_color)                                    \
  {                                             \
    (R), (G), (B)                               \
  })


typedef struct light
{
  enum light_type
  {
    DIRECTIONAL,
    POINT,
    AMBIANT,
  } type;
  s_color color;
  s_vect data;
} s_light;


typedef struct vertex
{
  s_vect v;
  s_vect vn;
} s_vertex;


typedef struct trian
{
  s_vertex vertices[3];
} s_trian;


typedef struct material
{
  s_color Ka;
  s_color Kd;
  s_color Ks;
  flt Ns;
  flt Ni;
  flt Nr;
  flt d;
} s_material;


#define DEFAULT_MATERIAL                        \
  ((s_material)                                 \
   {                                            \
     .Ka = COLOR(0, 0, 0),                      \
     .Kd = COLOR(0, 0, 0),                      \
     .Ks = COLOR(0, 0, 0),                      \
     .Ns = 0.,                                  \
     .Ni = 1.,                                  \
     .Nr = 0.,                                  \
     .d  = 1.,                                  \
   })


typedef struct object
{
  size_t count;
  s_material material;
  s_trian trians[];
} s_object;


typedef struct scene
{
  s_camera camera;
  size_t lights_count;
  s_light *lights;
  size_t objects_count;
  s_object *objects;
} s_scene;

s_scene *scene_parse(FILE *fout);
