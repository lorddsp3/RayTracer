#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main(){
    // Image
    // const int image_width = 256;
    // const int image_height = 256;
    const string out_filepath = "asset/output/writeppm1.ppm";
    // lets take that as input lol
    int image_width, image_height;
    cout << "Enter img width and height: ";
    cin >> image_width >> image_height;

    // file
    ofstream img_out(out_filepath);
    // render
    img_out << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j)
    {
        cerr << "Scanlines remaining: " << j << "\n";
        for (int i = 0; i < image_width; ++i)
        {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            img_out << ir << " " << ig << " " << ib << "\n";
        }
        cerr << "\n Done.\n";
    }
    // after rendering
    cout << "Opening Image via gnome image viewer\nfilepath: "<< out_filepath << endl;
    system(("gio open " + out_filepath).c_str());
    return 0;
}