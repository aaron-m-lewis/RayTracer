#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"
#include "ray.h"

int usage(int status) {
    printf("./run {width}\n");
    exit(status);
}

vec3 ray_color(ray r1) {
    // insert function for calculating pixel color based on ray direction
    vec3 direction_unit_vec = vec3_unit_vec(r1.direction);
    double a = (direction_unit_vec.y + 1.0) * 0.5;
    vec3 white_color = {1.0, 1.0, 1.0};
    vec3 green_color = {0.5, 1.0, 0.5};
    vec3 color = vec3_add(vec3_mult_scalar(white_color, 1.0 - a), vec3_mult_scalar(green_color, a));

    //vec3 color = {0.0, 0.0, 0.0};
    return color;
}

int main(int argc, char *argv[]) {
    
    // handle command line interaction
    if (argc != 2) usage(0);
    
    // create an output file in ppm (portable pixel map)) format
    FILE *output = fopen("output.ppm", "w");

    // define size of image with aspect ratio and width
    double aspect_ratio = 16.0 / 9.0;
    int width_pixels = atoi(argv[1]);

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
    vec3 viewport_Q_location = vec3_sub(camera_center, vec3_sub(temp_vec, vec3_sub(vec3_div(viewport_u, 2.0),vec3_div(viewport_v, 2.0))));
    vec3 p00_location = vec3_add(viewport_Q_location, vec3_mult_scalar(vec3_add(delta_u, delta_v), 0.5));

    // print image specifications to ppm file
    fprintf(output, "P3\n%d %d\n255\n", width_pixels, height_pixels);

    // generate basic graphics
    for (int i = 0; i < height_pixels; i++) {
        fprintf(stderr, "Currently on row %d/%d\n", i + 1, height_pixels);
        for (int j = 0; j < width_pixels; j++) {
            vec3 pixel_center = vec3_add(p00_location, vec3_add(vec3_mult_scalar(delta_u, j), vec3_mult_scalar(delta_v, i)));
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
