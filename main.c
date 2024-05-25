#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"
#include "ray.h"

int usage(int status) {
    printf("./run {width} {height}\n");
    exit(status);
}

int main(int argc, char *argv[]) {
    
    // handle command line interaction
    if (argc != 3) usage(0);
    
    // create an output file in ppm (portable pixel map)) format
    FILE *output = fopen("output.ppm", "w");
    
    // define size of image
    int width_pixels = atoi(argv[1]);
    int height_pixels = atoi(argv[2]);

    // print image specifications to ppm file
    fprintf(output, "P3\n%d %d\n255\n", width_pixels, height_pixels);

    // generate basic graphics
    for (int i = 0; i < height_pixels; i++) {
        fprintf(stderr, "Currently on row %d/%d\n", i + 1, height_pixels);
        for (int j = 0; j < width_pixels; j++) {
            vec3 color = {(double)(j) / (width_pixels - 1),
                          (double)(i) / (height_pixels - 1),
                          0.0};
            write_pixel_colors(output, color);
        }
        fprintf(output, "\n");
    }


    fclose(output);

    // success
    return 0;
}
