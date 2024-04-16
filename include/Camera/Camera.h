//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <chrono>

#include "../Rendering/Ray.h"
#include "../Rendering/Material.h"
#include "../Scene/Intersectable.h"

// Previously in main.cpp moved here to organize the program
class Camera {
public:
	// Scene
	void render (const Intersectable& scene);

	// Image
	int img_width = 1200;
	double aspect_ratio = 16.0 / 9.0;

	// Rendering
	// Antialiasing sampling
	int max_ray_depth = 30;
	int samp_per_pix  = 20;

	// Camera
	double vert_fov       = 20;
	Vec3 cam_origin       = Vec3 (13, 2, 3);
	Vec3 cam_facing_point = Vec3 (0, 0, 0);
	Vec3 v_up             = Vec3 (0, 1, 0);     // Camera's relative "up" direction
	double defocus_ang    = 0.6;                           // Variation angle of rays through each pixel
	double focus_dist     = 10;                            // Dist from cam_origin to best plane focus point

	void init ();

private:
	// Image
	int img_height = (int) (this->img_width / this->aspect_ratio);

	// Rendering
	const double pix_samp_scale = 1.0 / this->samp_per_pix;

	// Scene
	const Vec3 cam_center = this->cam_origin;

	Vec3 pix_dlt_u;
	Vec3 pix_dlt_v;
	Vec3 pix_sp_loc;
	Vec3 defocus_disk_u;
	Vec3 defocus_disk_v;
	const Vec3 w = unit_vec     (this->cam_origin - this->cam_facing_point);
	const Vec3 u = unit_vec     (cross_prod(this->v_up, this->w));
	const Vec3 v = cross_prod   (this->w, this->u);

	// Returns the vector to a random point in the [-0.5, -0.5] - [+0.5, +0.5] unit square.
	Vec3 samp_square () const;

	// Random point in the camera defocus disk
	Vec3 defocus_disk_samp () const;

	// Construct a camera ray originating from the origin
	// that is directed at randomly sampled point around the pixel location i, j
	Ray get_ray (const int height, const int width) const;

	// Determines the color of a given pixel using the ray bounce history
	Color ray_clr (const Ray&, int depth, const Intersectable& scene) const;
};


#endif //RAYTRACER_CAMERA_H
