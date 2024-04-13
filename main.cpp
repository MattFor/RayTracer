#include <iostream>

#include "./include/Vec3.h"
#include "./include/Color.h"

int main() {
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++)
    {
        std::clog << "\rScanlines remaining: " << image_height - i << ' ' << std::flush;

        for (int j = 0; j < image_width; j++)
        {
            Color::display(std::cout, Color ((double) i / (image_width - 1), (double) j / (image_height - 1), 0));
        }
    }

    std::clog << "\rOutput complete.\n";

    return 0;
}
