#include "color.h"
#include "vec3.h"
#include <fstream>
#include <string>
#include <iostream>

int main() {
    // lets take that as input lol
    int image_width, image_height;
    std::cout << "Enter img width and height: ";
    std::cin >> image_width >> image_height;

    // file
    const std::string out_filepath = "asset/output/" + std::to_string(image_width) + "x" + std::to_string(image_height) + ".ppm";
    std::ofstream img_out(out_filepath);
    // Render
    img_out << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::cout << "\rScanlines remaining: " << (image_height - j) << ' ' << std::endl;
        for (int i = 0; i < image_width; i++) {
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1), 0);
            write_color(img_out, pixel_color);
        }
    }
    std::cout << "DONE" << std::endl;
    std::cout << "Opening Image via gnome image viewer\nfilepath: "<< out_filepath << std::endl;
    system(("gio open " + out_filepath).c_str());
}