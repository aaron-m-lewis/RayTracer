#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "vec3.h"
#include "ray.h"

int usage(int status) {

    printf("./run {width}\n");
    exit(status);
}


//function determines at which time the ray intersects the surface of the sphere
double sphere_intersection(ray r1, vec3 origin, double radius) {

    vec3 p_to_c = vec3_sub(origin, r1.origin);
    double a = vec3_length_squared(r1.direction);
    double h = vec3_dot(r1.direction, p_to_c);
    double c = vec3_length_squared(p_to_c) - (radius * radius);
    double discriminant = h * h - a * c;

    if (discriminant < 0) return -1.0;
    else return (h - sqrt(discriminant)) / a;
}

//determines what color the pixel the ray passes through in the viewport should be
vec3 ray_color(ray r1) {

    vec3 sphere_loc = {0.0, 0.0, -1.0};
    double time = sphere_intersection(r1, sphere_loc, 0.5);
    if (time > 0.0) {
        vec3 normal = vec3_unit_vec(vec3_sub(ray_position(r1, time), sphere_loc));
        vec3 offset = {1.0, 1.0, 1.0};
        return vec3_mult_scalar(vec3_add(normal, offset), 0.5);
    }

    vec3 direction_unit_vec = vec3_unit_vec(r1.direction);
    double a = (direction_unit_vec.y + 1.0) * 0.5;
    vec3 white_color = {1.0, 1.0, 1.0};
    vec3 green_color = {0.5, 1.0, 0.5};
    vec3 color = vec3_add(vec3_mult_scalar(white_color, 1.0 - a), vec3_mult_scalar(green_color, a));

    return color;
}

int main(int argc, char *argv[]) {
    
    // handle command line interaction
    //if (argc != 2) usage(0);
    
    // create an output file in ppm (portable pixel map)) format
    FILE *output = fopen("output.ppm", "w");

    // define size of image with aspect ratio and width
    double aspect_ratio = 16.0 / 9.0;
    int width_pixels = 400;

    // calculate height_pixels based on aspect ratio and width
    int height_pixels = (int)(width_pixels / aspect_ratio);
    if (height_pixels < 1) height_pixels = 1;

    // define size of viewport based on height and aspect ratio, calculate width
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)(width_pixels) / height_pixels);

    // define camera traits
    double focal_length = 1.0;
    vec3 camera_center = {0.0, 0.0, 0.0};

    // viewport edge vectors
    vec3 viewport_u = {viewport_width, 0.0, 0.0};
    vec3 viewport_v = {0.0, -viewport_height, 0.0};

    // pixel deltas
    vec3 delta_u = vec3_div(viewport_u, width_pixels);
    vec3 delta_v = vec3_div(viewport_v, height_pixels);

    // calculating the location of the most upper left pixel in viewport from viewport upper left corner called "Q"
    vec3 temp_vec = {0, 0, focal_length};
    vec3 viewport_Q_location = vec3_sub(vec3_sub(vec3_sub(camera_center, temp_vec), vec3_div(viewport_u, 2.0)), vec3_div(viewport_v, 2.0));
    vec3 p00_location = vec3_add(viewport_Q_location, vec3_mult_scalar(vec3_add(delta_u, delta_v), 0.5));

    // print image specifications to ppm file
    fprintf(output, "P3\n%d %d\n255\n", width_pixels, height_pixels);

    // generate basic graphics
    for (int j= 0; j < height_pixels; j++) {
        fprintf(stderr, "Currently on row %d/%d\n", j + 1, height_pixels);
        for (int i = 0; i < width_pixels; i++) {
            vec3 pixel_center = vec3_add(p00_location, vec3_add(vec3_mult_scalar(delta_u, i), vec3_mult_scalar(delta_v, j)));
            vec3 ray_direciton = vec3_sub(pixel_center, camera_center);
            ray r1 = {camera_center, ray_direciton};
            vec3 pixel_color = ray_color(r1);
            write_pixel_colors(output, pixel_color);
        }
        fprintf(output, "\n");
    }


    fclose(output);

    // success
    return 0;
}
