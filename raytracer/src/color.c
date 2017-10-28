#include "color.h"


static inline flt flt_normalize(flt a)
{
  if (a < 0.)
    return 0.;
  if (a > 1.)
    return 1.;
  return a;
}


s_color color_compose(s_color a, s_color b)
{
  return COLOR(flt_normalize(a.r * b.r),
               flt_normalize(a.g * b.g),
               flt_normalize(a.b * b.b));
}
