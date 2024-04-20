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
			// Vec3 pix_center = this->pix_sp_loc + (j * this->pix_dlt_u) + (i * this->pix_dlt_v);
			// Vec3 ray_direction = pix_center - this->cam_center;
			// Ray r(this->cam_center, ray_direction);
			//
			// Color pix_clr = ray_clr(r, scene);
			// Color::display(std::cout, pix_clr);

			Color pix_clr (0.0, 0.0, 0.0);

			for (int k = 0; k < this->samp_per_pix; k++)
			{
				Ray r = this->get_ray(i, j);
				pix_clr += ray_clr(r, this->max_ray_depth, scene);
			}

			Color::display(std::cout, this->pix_samp_scale * pix_clr);
		}
	}

	std::chrono::duration <double> render_time = std::chrono::steady_clock::now() - start;
	std::clog << "Output complete. Render time: " << render_time.count() << " seconds\n";
}

void Camera::init ()
{
	this->img_height        =       (int) (this->img_width / this->aspect_ratio);
	this->img_height        =       (this->img_height < 1.0) ? 1.0 : this->img_height;

	this->cam_center        =       this->cam_origin;
	this->pix_samp_scale    =       1.0 / this->samp_per_pix;

	this->w                 =       unit_vec     (this->cam_origin - this->cam_facing_point);
	this->u                 =       unit_vec     (cross_prod(this->v_up, this->w));
	this->v                 =       cross_prod   (this->w, this->u);

	double theta            =       deg_to_rad(this->vert_fov);
	double h                =       std::tan(theta / 2.0);
	double viewport_height  =       2.0 * h * this->focus_dist;
	double viewport_width   =       viewport_height * ((double) this->img_width) / this->img_height;

	// Calculate vectors across horizontal and vertical viewport edges
	Vec3 viewport_u         =       viewport_width  *  this->u;
	Vec3 viewport_v         =       viewport_height * -this->v;

	// Calculate vertical and horizontal pixel deltas
	this->pix_dlt_u         =       viewport_u / this->img_width;
	this->pix_dlt_v         =       viewport_v / this->img_height;

	// Calculate location of top left pixel
	Vec3 viewport_top_left  =       this->cam_center - (this->focus_dist * this->w) - viewport_u / 2.0 - viewport_v / 2.0;
	this->pix_sp_loc        =       viewport_top_left + (this->pix_dlt_u + this->pix_dlt_v) * 0.5;

	double defocus_radius   =       this->focus_dist * std::tan(deg_to_rad(this->defocus_ang / 2.0));
	this->defocus_disk_u    =       u * defocus_radius;
	this->defocus_disk_v    =       v * defocus_radius;
}

// Private
Vec3 Camera::samp_square() const
{
	return Vec3(rand_double() - 0.5, rand_double() - 0.5, 0.0);
}

Vec3 Camera::defocus_disk_samp() const
{
	Vec3 point = rand_in_unit_disk();
	return this->cam_center + (point.x * this->defocus_disk_u) + (point.y * this->defocus_disk_v);
}

Ray Camera::get_ray (const int height, const int width) const
{
	Vec3 offset = this->samp_square();

	Vec3 pix_samp = this->pix_sp_loc                         +
			(((double) height + offset.y) * this->pix_dlt_v) +
			(((double) width +  offset.x) * this->pix_dlt_u);

	Vec3 ray_origin = this->defocus_ang <= 0.0 ? this->cam_center : this->defocus_disk_samp();
	Vec3 ray_direction = pix_samp - ray_origin;

	return Ray(ray_origin, ray_direction);
}

Color Camera::ray_clr (const Ray& r, int depth, const Intersectable& scene) const
{
	if (depth <= 0.0)
		return Color(0.0, 0.0, 0.0);

	IntersectionInfo info;

	// Added 0.001 instead of 0 to guard against floating point imprecision
	if (scene.hit(r, Range(0.0001, INF), info))
	{
		// OLD^2:
		// return (info.norm + Color(1, 1, 1)) * 0.5;
		// Now unused since we have introduced reflective materials

		// OLD:
		// // Adding info.norm to randomly generate the vector according to the Lambertian distribution
		// Vec3 dir = info.norm + rand_on_hemisphere(info.norm);
		// return ray_clr(Ray(info.i_point, dir), --depth, scene) * 0.8;
		// Now unused since there are materials present which have their own ways of influencing light bounces

		Ray scattered;
		Color attenuation;

		if (info.mat->scatter_light(r, info, attenuation, scattered))
		{
			return attenuation * ray_clr(scattered, depth - 1, scene);
		}

		return Color(0.0, 0.0, 0.0);
	}

	// Unused since hit detection has been moved to stuff related to Scene
	//    // Vector scalar to represent its way along the 3D line
	//    double s = sphere_intersection(Vec3(0, 0, -1), 0.5, r);
	//
	//    if (s > 0)
	//    {
	//        Vec3 norm_vec = unit_vec(r.pos_at(s) - Vec3(0, 0, -1));
	//        return Color(norm_vec.x + 1, norm_vec.y + 1, norm_vec.z + 1) * 0.5;
	//    }

	Vec3 unit_dir = unit_vec(r.direction());
	double A = (unit_dir.y + 1.0) * 0.5;

	return (1.0 - A) * Color {1.0, 1.0, 1.0} + A * Color (0.5, 0.7, 1.0);
}
