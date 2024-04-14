//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <chrono>
#include <iostream>

#include "../RayTracer.h"
#include "../Scene/Intersectable.h"

// Previously in main.cpp moved here to organize the program
class Camera {
public:
	// Scene
	void render (const Intersectable& scene);

	// Image
	const int img_width = 1024;
	const double aspect_ratio = 16.0 / 9.0;

	// Rendering
	// Antialiasing sampling
	const int samp_per_pixel = 10;

	void init ();

private:
	// Image
	int img_height = (int) (this->img_width / this->aspect_ratio);

	// Rendering
	const double pix_samp_scale = 1.0 / this->samp_per_pixel;

	// Scene
	const Vec3 cam_center = Vec3 (0.0, 0.0, 0.0);

	Vec3 pix_dlt_u;
	Vec3 pix_dlt_v;
	Vec3 pix_sp_loc;

	// Returns the vector to a random point in the [-0.5, -0.5] - [+0.5, +0.5] unit square.
	Vec3 samp_square () const;

	// Construct a camera ray originating from the origin
	// that is directed at randomly sampled point around the pixel location i, j
	Ray get_ray (const int height, const int width) const;

	// Determines the color of a given pixel using the ray bounce history
	Color ray_clr (const Ray&, const Intersectable& scene) const;
};


#endif //RAYTRACER_CAMERA_H
