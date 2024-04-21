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

	// These settings are set in main.cpp (these are just examples)
	// Image
	int img_width;
	double aspect_ratio;

	// Rendering
	// Antialiasing sampling
	int samp_per_pix;
	int max_ray_depth;

	// Camera
	double vert_fov;        // Vertical viewing angle (i.e. field of view)
	double focus_dist;      // Dist from cam_origin to best plane focus point
	double defocus_ang;     // Variation angle of rays through each pixel

	Vec3 v_up;              // Camera's relative "up" direction
	Vec3 cam_origin;
	Vec3 cam_facing_point;

private:
	// Image
	int img_height;

	// Rendering
	double pix_samp_scale;

	// Scene
	Vec3 u, v, w;
	Vec3 cam_center;
	Vec3 pix_sp_loc;
	Vec3 pix_dlt_u, pix_dlt_v;
	Vec3 defocus_disk_u, defocus_disk_v;

	void init ();

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
