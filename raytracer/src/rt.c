#include <err.h>
#include <stdio.h>

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

  // TODO

  fclose(fin);
  fclose(fout);
  return 0;
}
