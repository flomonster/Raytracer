#include <ppm.h>
#include <stdlib.h>
#include <stdio.h>



s_image *image_alloc(size_t w, size_t h)
{
  s_image *ret = malloc(sizeof(*ret) + sizeof(s_pix) * w * h);
  if (!ret)
    return NULL;
  ret->h = h;
  ret->w = w;
  return ret;
}


static inline void put_component(flt comp, FILE *out)
{
  int curval = comp * 255;
  fprintf(out, "%4d", curval);
}

static void put_pixel(s_pix *pix, FILE *out)
{
  put_component(pix->r, out);
  put_component(pix->g, out);
  put_component(pix->b, out);
}


void image_render(s_image *img, FILE *out)
{
  fputs("P3\n", out);
  fprintf(out, "%zu %zu\n", img->w, img->h);
  fputs("255\n", out);

  for (size_t y = 0; y < img->h; y++)
    for (size_t x = 0; x < img->w; x++)
      put_pixel(&img->pix[img->w * y + x], out);
}
