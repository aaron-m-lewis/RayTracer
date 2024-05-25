#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// STRUCT //////////////////////////////////////////////////////////////////

typedef struct ray {

    vec3 origin;
    vec3 direction;

} ray;

// ray functions //////////////////////////////////////////////////////////////////

vec3 ray_position(ray r1, double time) {
    return vec3_add(r1.origin, vec3_mult_scalar(r1.direction, time));
}

#endif
