#ifndef VEC3_H
#define VEC3_H

#include <math.h>

// STRUCT //////////////////////////////////////////////////////////////////

typedef struct Vec3 {

    double x;
    double y;
    double z;

} Vec3;

// vec3 functions //////////////////////////////////////////////////////////////////

Vec3 vec3_add(Vec3 v1, Vec3 v2) {
    Vec3 resultant = {v1.x + v2.x,
                      v1.y + v2.y,
                      v1.z + v2.z};
    return resultant;
}

Vec3 vec3_sub(Vec3 v1, Vec3 v2) {
    Vec3 resultant = {v1.x - v2.x,
                      v1.y - v2.y,
                      v1.z - v2.z};
    return resultant;
}

Vec3 vec3_mult_scalar(Vec3 v1, double num) {
    Vec3 resultant = {v1.x * num,
                      v1.y * num,
                      v1.z * num};
    return resultant;
}

Vec3 vec3_mult_vec3(Vec3 v1, Vec3 v2) {
    Vec3 resultant = {v1.x * v2.x,
                      v1.y * v2.y,
                      v1.z * v2.z};
    return resultant;
}

Vec3 vec3_div(Vec3 v1, double num) {
    Vec3 resultant = {v1.x / num,
                      v1.y / num,
                      v1.z / num};
    return resultant;
}

double vec3_dot(Vec3 v1, Vec3 v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

Vec3 vec3_cross(Vec3 v1, Vec3 v2) {
    Vec3 resultant = {v1.y * v2.z - v1.z * v2.y,
                      v1.z * v2.x - v1.x * v2.z,
                      v1.x * v2.y - v1.y * v2.x};
    return resultant;
}

double vec3_length_squared(Vec3 v1) {
    return pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2);
}

double vec3_length(Vec3 v1) {
    return sqrt(vec3_length_squared(v1));
}

Vec3 vec3_unit_vec(Vec3 v1) {
    double length = vec3_length(v1);
    Vec3 resultant = {v1.x / length,
                      v1.y / length,
                      v1.z / length};
    return resultant;
}

Vec3 vec3_negative(vec3 v1) {
    Vec3 resultant = {-v1.x,
                      -v1.y,
                      -v1.z};
    return resultant;
}

// color (vec3) functions //////////////////////////////////////////////////////////////////
// color is just a vec3, where each "dimension" represents color value

void write_pixel_colors(FILE *destination, Vec3 v1) {

    // rgb values in range [0, 1] 
    double red = v1.x;
    double green = v1.y;
    double blue = v1.z;

    // rgb values in range [0, 255]
    int red_int = red * 255.999;
    int green_int = green * 255.999;
    int blue_int = blue * 255.999;

    fprintf(destination, "%d %d %d\t", red_int, green_int, blue_int);
}

#endif
