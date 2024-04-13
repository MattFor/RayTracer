#include <iostream>

int main() {
    int image_width = 256;
    int image_height = 256;

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int i = 0; i < image_height; i++)
    {
        std::clog << "\rScanlines remaining: " << image_height - i << ' ' << std::flush;

        for (int j = 0; j < image_width; j++) {
            double _red = (double) i / (image_width - 1);
            double _green = (double) j / (image_height - 1);
            double _blue = 0.0f;

            int red = (int)(255.999 * _red);
            int green = (int)(255.999 * _green);
            int blue = (int)(255.999 * _blue);

            std::cout << red << ' ' << green << ' ' << blue << '\n';
        }
    }

    std::clog << "\rOutput complete.\n";

    return 0;
}
