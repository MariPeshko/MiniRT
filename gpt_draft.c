// Very small RT prorgams for
// general understanding if a structure

#include <stdio.h>
#include <math.h>

typedef struct {
    double x, y, z;
} Vec3;

typedef struct {
    Vec3 center;
    double radius;
} Sphere;

Vec3 subtract(Vec3 a, Vec3 b) {
    return (Vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

double dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int intersect_ray_sphere(Vec3 origin, Vec3 dir, Sphere sphere, double *t) {
    Vec3 oc = subtract(origin, sphere.center);
    double b = 2.0 * dot(oc, dir);
    double c = dot(oc, oc) - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * c;

    if (discriminant < 0) return 0;
    *t = (-b - sqrt(discriminant)) / 2.0;
    return (*t > 0);
}

void render_sphere(int width, int height) {
    Vec3 camera = {0, 0, -5};  
    Sphere sphere = {{0, 0, 0}, 1};  
    printf("Content-Type: image/ppm\n\n");
    printf("P3\n%d %d\n255\n", width, height);

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            Vec3 ray_dir = {(x - width / 2) / (double)width, 
                            (y - height / 2) / (double)height, 1};
            double t;
            if (intersect_ray_sphere(camera, ray_dir, sphere, &t)) {
                int color = (int)(255 * (1 - t / 5));
                printf("%d %d %d ", color, color, color);
            } else {
                printf("0 0 0 ");
            }
        }
        printf("\n");
    }
}

int main() {
    render_sphere(200, 200);
    return 0;
}
