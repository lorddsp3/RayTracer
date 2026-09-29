#include <fstream>
#include <string>
#include <iostream>
#include <format>

#include "color.h"
#include "vec3.h"
#include "ray.h"
#include "../asset/extra/libs/progressbar.hpp"


bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}

color ray_color(const ray& r) {
    if (hit_sphere(point3(0,0,-1), 0.5, r))
        return color(1, 0, 0);
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // lets take that as input lol
    int image_width, image_height;
    std::cout << "Enter img width and height: ";
    std::cin >> image_width >> image_height;

    // Camera
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);
    
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    // file
    const std::string out_filepath = "asset/output/" + std::to_string(image_width) + "x" + std::to_string(image_height) + ".ppm";
    std::ofstream img_out(out_filepath);
    // Render
    img_out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    progressbar bar(image_height);
    for (int j = 0; j < image_height; j++) {
        bar.update(std::format("\rScanlines remaining: {}/{}", j+1, image_height));
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(img_out, pixel_color);
        }
    }
    std::cout << "DONE" << std::endl;
    std::cout << "Opening Image via gnome image viewer\nfilepath: "<< out_filepath << std::endl;
    system(("gio open " + out_filepath).c_str());
}