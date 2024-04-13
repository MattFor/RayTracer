//
// Created by MattFor on 13.04.2024.
//

#include <iostream>

#include "include/Basics/Ray.h"
#include "include/Basics/Vec3.h"
#include "include/Basics/Color.h"

double sphere_intersection (const Vec3& center, const double radius, const Ray& r)
{
    // A, B, C as in y = Ax^2 + Bx + C

    Vec3 origin_to_center = center - r.origin();

    double A = r.direction().len_squared();
    // OLD: double B = dot_prod(r.direction(), origin_to_center) * -2.0;
    double H = dot_prod(r.direction(), origin_to_center);
    double C = origin_to_center.len_squared() - radius*radius;

    // Δ > 0 - 2 intersection points
    // Δ == 0 - 1 intersection point
    // Δ < 0 - 0 intersection points
    // OLD: double dlt = B*B - 4*A*C;
    // Changed because:
    // - vector dotted with itself is just the length of itself squared
    // - the equation simplifies if "-2H" is substituted for "B"
    double dlt = H*H - A*C;

    if (dlt < 0)
    {
        return -1.0;
    }
    else
    {
        // OLD: return (-B - sqrt(dlt)) / (2.0 * A);
        return (H - sqrt(dlt)) / A;
    }
}

Color ray_clr (const Ray& r)
{
    // Vector scalar to represent its way along the 3D line
    double s = sphere_intersection(Vec3(0, 0, -1), 0.5, r);

    if (s > 0.0)
    {
        Vec3 norm_vec = unit_vec(r.pos_at(s) - Vec3(0, 0, -1));
        return Color(norm_vec.x + 1, norm_vec.y + 1, norm_vec.z + 1) * 0.5;
    }

    Vec3 unit_dir = unit_vec(r.direction());
    double A = (unit_dir.y + 1.0) * 0.5;

    return (1.0 - A) * Color {1.0, 1.0, 1.0} + A * Color (0.5, 0.7, 1.0);
}

int main() {
    // Image
    double aspect_ratio = 16.0 / 9.0;

    int img_width = 400;
    int img_height = (int) (img_width / aspect_ratio);
    img_height = (img_height < 1) ? 1 : img_height;

    // Camera
    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double) img_width) / img_height;

    Vec3 cam_center = Vec3 (0, 0, 0);

    // Calculate vectors across horizontal and vertical viewport edges
    Vec3 viewport_u = Vec3 (viewport_width, 0, 0);
    Vec3 viewport_v = Vec3(0, -viewport_height, 0);

    // Calculate vertical and horizontal pixel deltas
    Vec3 pix_dlt_u = viewport_u / img_width;
    Vec3 pix_dlt_v = viewport_v / img_height;

    // Calculate location of top left pixel
    Vec3 viewport_top_left = cam_center - Vec3 (0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
    Vec3 pix_sp_loc = viewport_top_left + (pix_dlt_u + pix_dlt_v) * 0.5;

    // Renderer
    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int i = 0; i < img_height; i++)
    {
        std::clog << "\rScanlines remaining: " << img_height - i << ' ' << std::flush;

        for (int j = 0; j < img_width; j++)
        {
            Vec3 pix_center = pix_sp_loc + (j * pix_dlt_u) + (i * pix_dlt_v);
            Vec3 ray_dir = pix_center - cam_center;

            Ray ray (cam_center, ray_dir);
            Color::display(std::cout, ray_clr(ray));
        }
    }

    std::clog << "\rOutput complete.\n";

    return 0;
}
