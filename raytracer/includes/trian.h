#pragma once

#include <stdbool.h>

#include "svati.h"


flt trian_intersect(const s_trian *tri, const s_ray *ray,
                    s_ray *res);
