#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

// STRUCT //////////////////////////////////////////////////////////////////

typedef struct Ray {

    Vec3 origin;
    Vec3 direction;

} Ray;

// ray functions //////////////////////////////////////////////////////////////////

vec3 ray_position(Ray r1, double time) {
    return vec3_add(r1.origin, vec3_mult_scalar(r1.direction, time));
}

#endif
