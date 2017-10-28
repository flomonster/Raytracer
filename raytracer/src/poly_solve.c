#include <defs.h>
#include <math.h>

unsigned resolve_quadratic(flt *roots, flt *coefs)
{
  flt delta = pow(coefs[1], 2) - 4. * coefs[0] * coefs[2];
  if (delta == 0) // unlikely to ever run
  {
    roots[0] = -(coefs[1]) / (2. * coefs[0]);
    return 1;
  }
  else if (delta > 0)
  {
    roots[0] = (-coefs[1] - sqrt(delta)) / (2. * coefs[0]);
    roots[1] = (-coefs[1] + sqrt(delta)) / (2. * coefs[0]);
    return 2;
  }
  else
    return 0;
}
