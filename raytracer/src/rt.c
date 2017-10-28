#include <err.h>
#include <stdio.h>
#include <stdlib.h>

#include "svati.h"
#include "render.h"
#include "ppm.h"
#include "print.h"


int main(int argc, char **argv)
{
  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <input> <output>\n", argv[0]);
    return 1;
  }

  FILE *fin = fopen(argv[1], "r");
  if (!fin)
    err(2, "can't open '%s'.", argv[1]);

  FILE *fout = fopen(argv[2], "w");
  if (!fout)
  {
    fclose(fin);
    err(3, "can't open '%s'.", argv[2]);
  }

  s_scene *scene = scene_parse(fin);
  // scene_print(scene);
  s_image *img = scene_render(scene);
  image_render(img, fout);
  free(img);

  scene_destroy(scene);

  fclose(fin);
  fclose(fout);
  return 0;
}
