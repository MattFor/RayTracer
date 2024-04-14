//
// Created by MattFor on 14.04.2024.
//

#include "../../include/Camera/Camera.h"

// Public
void Camera::render (const Intersectable& scene)
{
	// Renderer
	std::cout << "P3\n" << this->img_width << ' ' << this->img_height << "\n255\n";

	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	for (int i = 0; i < this->img_height; i++)
	{
		std::clog << "\rScanlines remaining: " << this->img_height - i << ' ' << std::flush;

		for (int j = 0; j < this->img_width; j++)
		{
			Color pix_clr (0, 0, 0);

			for (int k = 0; k < this->samp_per_pixel; k++)
			{
				Ray r = this->get_ray(i, j);
				pix_clr += ray_clr(r, scene);
			}

			Color::display(std::cout, this->pix_samp_scale * pix_clr);
		}
	}

	std::chrono::duration <double> render_time = std::chrono::steady_clock::now() - start;
	std::clog << "Output complete. Render time: " << render_time.count() << " seconds\n";
}

void Camera::init ()
{
	this->img_height = (this->img_height < 1) ? 1 : this->img_height;

	double focal_length = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double) this->img_width) / this->img_height;

	// Calculate vectors across horizontal and vertical viewport edges
	Vec3 viewport_u = Vec3 (viewport_width, 0, 0);
	Vec3 viewport_v = Vec3(0, -viewport_height, 0);

	// Calculate vertical and horizontal pixel deltas
	this->pix_dlt_u = viewport_u / this->img_width;
	this->pix_dlt_v = viewport_v / this->img_height;

	// Calculate location of top left pixel
	Vec3 viewport_top_left = this->cam_center - Vec3 (0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	this->pix_sp_loc = viewport_top_left + (this->pix_dlt_u + this->pix_dlt_v) * 0.5;
}

// Private
Vec3 Camera::samp_square() const
{
	return Vec3(rand_double() - 0.5, rand_double() - 0.5, 0);
}

Ray Camera::get_ray (const int i, const int j) const
{
	Vec3 offset = this->samp_square();

	Vec3 pix_samp = this->pix_sp_loc                    +
			(((double) i + offset.y) * this->pix_dlt_v) +
			(((double) j + offset.x) * this->pix_dlt_u);

	Vec3 ray_origin = this->cam_center;
	Vec3 ray_direction = pix_samp - ray_origin;

	return Ray(ray_origin, ray_direction);
}

Color Camera::ray_clr (const Ray& r, const Intersectable& scene) const
{
	IntersectionInfo info;

	if (scene.hit(r, Range(0, INF), info))
	{
		return (info.norm + Color(1, 1, 1)) * 0.5;
	}

	// Unused since hit detection has been moved to stuff related to Scene
	//    // Vector scalar to represent its way along the 3D line
	//    double s = sphere_intersection(Vec3(0, 0, -1), 0.5, r);
	//
	//    if (s > 0.0)
	//    {
	//        Vec3 norm_vec = unit_vec(r.pos_at(s) - Vec3(0, 0, -1));
	//        return Color(norm_vec.x + 1, norm_vec.y + 1, norm_vec.z + 1) * 0.5;
	//    }

	Vec3 unit_dir = unit_vec(r.direction());
	double A = (unit_dir.y + 1.0) * 0.5;

	return (1.0 - A) * Color {1.0, 1.0, 1.0} + A * Color (0.5, 0.7, 1.0);
}
