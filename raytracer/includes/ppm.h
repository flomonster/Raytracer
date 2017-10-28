#pragma once

#include "svati.h"
#include <stddef.h>
#include <stdio.h>


typedef s_color s_pix;
#define PIX(R, G, B) COLOR(R, G, B)


typedef struct image
{
  size_t w;
  size_t h;
  s_pix pix[];
} s_image;


#define IMG_AT(Img, X, Y) ((Img)->pix[(Img)->w * (Y) + (X)])

s_image *image_alloc(size_t w, size_t h);
void image_render(s_image *img, FILE *out);
