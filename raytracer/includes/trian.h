#pragma once

#include <stdbool.h>
#include <svati.h>

bool trian_intersect(const s_trian *tri, const s_ray *ray, s_ray *res);
