//
// Created by MattFor on 13.04.2024.
//

#include "include/RayTracer.h"

#include "include/Camera/Camera.h"
#include "include/Scene/Intersectable.h"
#include "include/Scene/IntersectableList.h"
#include "include/Rendering/Material.h"
#include "include/Scene/Sphere.h"

// ! Now unused. Moved to its own folder with Intersectable related code
//double sphere_intersection (const Vec3& center, const double radius, const Ray& r)
//{
//    // A, B, C as in y = Ax^2 + Bx + C
//
//    Vec3 origin_to_center = center - r.origin();
//
//    double A = r.direction().len_squared();
//    // OLD: double B = dot_prod(r.direction(), origin_to_center) * -2;
//    double H = dot_prod(r.direction(), origin_to_center);
//    double C = origin_to_center.len_squared() - radius*radius;
//
//    // Δ > 0 - 2 intersection points
//    // Δ == 0 - 1 intersection point
//    // Δ < 0 - 0 intersection points
//    // OLD: double dlt = B*B - 4*A*C;
//    // Changed because:
//    // - vector dotted with itself is just the length of itself squared
//    // - the equation simplifies if "-2H" is substituted for "B"
//    double dlt = H*H - A*C;
//
//    if (dlt < 0)
//    {
//        return -1;
//    }
//    else
//    {
//        // OLD: return (-B - sqrt(dlt)) / (2 * A);
//        return (H - sqrt(dlt)) / A;
//    }
//}

int main()
{
	IntersectableList scene;

	// OLD OLD:
	//
	// // OLD setup of spheres
	// // scene.add (std::make_shared <Sphere> (Vec3(0, 0, -1), 0.5));
	// // scene.add (std::make_shared <Sphere> (Vec3(0, -100.5, -1), 100));
	//
	std::shared_ptr <Lambertian> mat_ground = std::make_shared <Lambertian> (Color(0.8, 0.8, 0));
	std::shared_ptr <Lambertian> mat_center = std::make_shared <Lambertian> (Color(0.1, 0.2, 0.5));
	std::shared_ptr <Metal>      mat_left   = std::make_shared <Metal>      (Color(0.8, 0.8, 0.8), 0.3);
	// std::shared_ptr <Dielectric> mat_left   = std::make_shared <Dielectric> (1.5);
	std::shared_ptr <Dielectric> mat_bubble = std::make_shared <Dielectric> (1.0 / 1.5);
	std::shared_ptr <Metal>      mat_right  = std::make_shared <Metal>      (Color(0.8, 0.6, 0.2), 1.0);

	scene.add(std::make_shared <Sphere> (Vec3( 0.0,    -100.5, 1.0), 100.0, mat_ground));
	scene.add(std::make_shared <Sphere> (Vec3( 0.0,    0.0,    1.2),   0.5, mat_center));
	scene.add(std::make_shared <Sphere> (Vec3( -1.0,   0.0,    1.0),   0.5, mat_left));
	// scene.add(std::make_shared <Sphere> (Vec3( -1,   0,    -1),   0.4, mat_bubble));
	scene.add(std::make_shared <Sphere> (Vec3( 1.0,    0.0,    1.0),   0.5, mat_right));
	//
	//
	// const double R = std::cos(PI / 4.0);
	// std::shared_ptr <Lambertian> mat_left  = std::make_shared <Lambertian> (Color(0.0, 0.0, 1.0));
	// std::shared_ptr <Lambertian> mat_right = std::make_shared <Lambertian> (Color(1.0, 0.0, 0.0));
	//
	// scene.add(std::make_shared <Sphere> (Vec3(-R, 0.0, 1.0), R, mat_left));
	// scene.add(std::make_shared <Sphere> (Vec3( R, 0.0, 1.0), R, mat_right));
	//
	// std::shared_ptr <Lambertian> ground_mat = std::make_shared <Lambertian> (Color(0.5, 0.5, 0.5));
	// scene.add(std::make_shared <Sphere> (Vec3(0.0, -1000.0, 0.0), 1000.0, ground_mat));
	//
	// for (int a = -11; a < 11; a++)
	// {
	// 	for (int b = -11; b < 11; b++)
	// 	{
	// 		double choose_mat = rand_double();
	// 		Vec3 center(a + 0.9 * rand_double(), 0.2, b + 0.9 * rand_double());
	//
	// 		if ((center - Vec3(4.0, 0.2, 0.0)).len() > 0.9)
	// 		{
	// 			std::shared_ptr <Material> sphere_material;
	//
	// 			if (choose_mat < 0.8)
	// 			{
	// 				// diffuse
	// 				Vec3 albedo = Vec3::rand()*Vec3::rand();
	// 				sphere_material = std::make_shared <Lambertian> (albedo);
	// 				scene.add(std::make_shared <Sphere> (center, 0.2, sphere_material));
	// 			}
	// 			else if (choose_mat < 0.95)
	// 			{
	// 				// Metal
	// 				Vec3 albedo = Vec3::rand(0.5, 1.0);
	// 				double fuzz = rand_double(0.0, 0.5);
	// 				sphere_material = std::make_shared <Metal> (albedo, fuzz);
	// 				scene.add(std::make_shared <Sphere> (center, 0.2, sphere_material));
	// 			}
	// 			else
	// 			{
	// 				// glass
	// 				sphere_material = std::make_shared <Dielectric> (1.5);
	// 				scene.add(std::make_shared <Sphere> (center, 0.2, sphere_material));
	// 			}
	// 		}
	// 	}
	// }
	//
	// std::shared_ptr <Dielectric> mat1 = std::make_shared <Dielectric> (1.5);
	// std::shared_ptr <Lambertian> mat2 = std::make_shared <Lambertian> (Color(0.4, 0.2, 0.1));
	// std::shared_ptr <Metal>      mat3 = std::make_shared <Metal>      (Color(0.7, 0.6, 0.5), 0.0);
	//
	// scene.add(std::make_shared <Sphere> (Vec3(0.0, 1.0, 0.0), 1.4, mat1));
	// scene.add(std::make_shared <Sphere> (Vec3(-4.0,1.0, 0.0), 1.2, mat2));
	// scene.add(std::make_shared <Sphere> (Vec3(4.0, 1.0, 0.0), 1.0, mat3));

	// Camera
	Camera cam;

	cam.img_width           = 400;
	cam.aspect_ratio        = 16.0 / 9.0;

	cam.samp_per_pix        = 20;
	cam.max_ray_depth       = 10;

	cam.vert_fov            = 120.0;
	cam.focus_dist          = 1.0;
	cam.defocus_ang         = 0.0;

	cam.v_up                = Vec3 (0.0, 1.0, 0.0);

	// Looking from here
	cam.cam_origin          = Vec3 (0.0, 0.0, 0.0);

	// Looking at this
	cam.cam_facing_point    = Vec3 (0.0, 0.0, 1.0);

	// cam.img_width           = 512;
	// cam.aspect_ratio        = 16 / 9;
	//
	// cam.samp_per_pix        = 30;
	// cam.max_ray_depth       = 20;
	//
	// cam.vert_fov            = 90;
	// cam.focus_dist          = 1;
	// cam.defocus_ang         = 1;
	// cam.v_up                = Vec3 (0, 1, 0);
	// cam.cam_origin          = Vec3 (0, 0, 0);
	// cam.cam_facing_point    = Vec3 (0, 0, -1);

	cam.init   ();
	cam.render (scene);

    return 0;
}
