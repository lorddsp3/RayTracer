#ifndef CAMERA_H
#define CAMERA_H

#include <fstream>
#include <string>
#include <format>

#include "hittable.h"
#include "color.h"
#include "../asset/extra/libs/progressbar.hpp"

#include <limits>

enum class image_size_mode {
    default_size,       // use width + height already defined
    width_only,         // enter width, calculate height
    width_and_height    // enter both manually
};

class camera {
    public:
        image_size_mode size_mode = image_size_mode::default_size;
        double aspect_ratio = 1.0;  // Ratio of image width over height
        int    image_width  = 400, image_height=225;  // Rendered image width,height in pixel count

        void render(const hittable& world) {
            initialize();    
            // file
            const std::string out_filepath = "asset/output/" + std::to_string(image_width) + "x" + std::to_string(image_height) + ".ppm";
            std::ofstream img_out(out_filepath);
            progressbar bar(image_height);

            img_out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for (int j = 0; j < image_height; j++) {
                bar.update(std::format("\rScanlines : {}/{}", j+1, image_height));
                // std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
                for (int i = 0; i < image_width; i++) {
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - center;
                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(img_out, pixel_color);
                }
            }
            std::cout << "DONE" << std::endl;
            std::cout << "Opening Image via gnome image viewer\nfilepath: "<< out_filepath << std::endl;
            system(("gio open " + out_filepath).c_str());
        }

  private:
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below


    void initialize() {
        if (size_mode == image_size_mode::width_only) {
            std::cout << "Enter image width: ";
            std::cin >> image_width;
            image_height = static_cast<int>(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

        } else if (size_mode == image_size_mode::width_and_height) {
            std::cout << "Enter image width and height: ";
            std::cin >> image_width >> image_height;
        } // else default size 400:225
        
        

        center = point3(0, 0, 0);

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world) const {
        hit_record rec;

        if (world.hit(r, interval(0, std::numeric_limits<double>::infinity()), rec)) {
            return 0.5 * (rec.normal + color(1,1,1));
        }

        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }
};

#endif
