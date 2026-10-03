#ifndef IMG_COUNT_HPP
#define IMG_COUNT_HPP

#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

inline std::string generate_image_path(
    const std::string& folder_path,
    int image_width,
    int image_height,
    const std::string& image_name = "",
    const std::string& extension = ".ppm")
{
    // Create output folder if it doesn't exist
    std::filesystem::create_directories(folder_path);

    // Counter is always stored here
    const std::filesystem::path counter_file =
        "asset/input/counter.db";

    // Create counter directory if needed
    std::filesystem::create_directories(counter_file.parent_path());

    // Read counter
    int counter = 1;

    {
        std::ifstream in(counter_file);

        if (in >> counter) {
            // Counter successfully read
        }
    }

    // Build filename
    std::ostringstream filename;

    filename << std::setfill('0')
             << std::setw(3)
             << counter
             << "_";

    if (image_name.empty()) {
        filename << image_height
                 << "x"
                 << image_width;
    }
    else {
        filename << image_name
                 << "_"
                 << image_height
                 << "x"
                 << image_width;
    }

    filename << extension;

    // Full output path
    std::filesystem::path full_path =
        std::filesystem::path(folder_path) / filename.str();

    // Save next counter
    {
        std::ofstream out(counter_file);
        out << counter + 1;
    }

    return full_path.string();
}

#endif