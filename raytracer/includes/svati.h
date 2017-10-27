#pragma once

#include <stddef.h>


typedef double flt;

typedef struct vector3
{
  flt x;
  flt y;
  flt z;
} s_vector3;

typedef s_vector3 s_vector;


typedef struct camera
{
  size_t width;
  size_t height;
  s_vector pos;
  s_vector u;
  s_vector v;
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


typedef struct lights
{
  enum light_type
  {
    DIRECTIONAL,
    POINT,
    AMBIANT,
  } type;
  s_color color;
  s_vector data;
} s_lights;


typedef struct vertex
{
  s_vector v;
  s_vector vn;
} s_vertex;


typedef struct trian
{
  struct s_vertex vertices[3];
};


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
  s_trian trians;
} s_object;
