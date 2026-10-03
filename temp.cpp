#include <iostream>
#include "asset/extra/libs/img_count.hpp"

int main()
{
    std::cout << generate_image_path(
        "asset/output",
        1920,
        1080
    ) << '\n';

    std::cout << generate_image_path(
        "asset/output",
        800,
        600,
        "sphere"
    ) << '\n';

    std::cout << generate_image_path(
        "asset/output",
        1280,
        720,
        "render",
        ".png"
    ) << '\n';

    std::cout << generate_image_path(
        "asset/output",
        640,
        480,
        "",
        ".png"
    ) << '\n';

    return 0;
}