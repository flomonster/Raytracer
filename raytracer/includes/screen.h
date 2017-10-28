#pragma once


#include "defs.h"
#include "vect.h"
#include "svati.h"
#include "ray.h"


typedef struct screen
{
  s_vect w;
  s_vect C;
  flt L;
} s_screen;

s_screen screen_init(const s_camera *cam);
s_ray screen_raycast(const s_screen *scr, const s_camera *cam, size_t x, size_t y);
