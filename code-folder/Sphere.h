#ifndef SPHERE_H
#define SPHERE_H

#include "Vec3.h"
#include "Surface.h"



// STRUCT (SPHERE) //////////////////////////////////////////////////////////////////
//
typedef struct Sphere {
    Vec3 center;
    double radius
    Surface surface_data;
} Sphere;

bool sphere_hit(Sphere s1, Ray r1, double t_min, double t_max, Surface hit) {
    
    Vec3 p_to_c = vec3_sub(s1.center, r1.origin);
    double a = vec3_length_squared(r1.direction);
    double h = vec3_dot(r1.direction, p_to_c);
    double c = vec3_length_squared(p_to_c) - (s1.radius * s1.radius);
    double discriminant = h * h - a * c;

    if (discriminant < 0) return false;

    double discriminant_sqrt = sqrt(discriminant);
    double root = (h - descriminant_sqrt) / a;
    if (root <= t_min || t_max <= root) {
        root = (h + descriminant_sqrt) / a;
        if (root <= t_min || t_max <= root) return false;
    }

    hit.time = root;
    hit.p = ray_position(r1, root);
    Vec3 outside_normal = vec3_div(vec3_sub(hit.p, s1.center), s1.radius);
    set_normal_face(s1.surface_data, r1, outside_normal);

    return true;

}

#endif
