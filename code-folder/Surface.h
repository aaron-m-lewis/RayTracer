#ifndef SURFACE_H
#define SURFACE_H

#include "Ray.h"

// STRUCT (SURFACE_HIT) //////////////////////////////////////////////////////////////////
typedef struct Surface {
   Vec3 p;
   Vec3 normal_vec;
   double time;
   bool outside_face;
} Surface;

void set_normal_face(Surace surface1, Ray r1, Vec3 outside_normal) {
    
    if (vec3_dot(r1.direction, outside_normal) < 0) surface1.outside_face = true;
    else surface1.outside_face = false;

    // good old ternary operator
    surface1.normal_vec = surface1.outside_face ? outside_normal : vec3_negative(outside_normal);
}

#endif
