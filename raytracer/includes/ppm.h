#pragma once

#include "svati.h"
#include <stddef.h>
#include <stdio.h>


typedef image
{
  size_t w;
  size_t h;
  s_color pix[];
} s_image;


s_image *image_alloc(size_t w, size_t h);
bool image_render(s_image *img, FILE *out);
