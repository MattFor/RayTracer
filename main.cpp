//
// Created by MattFor on 13.04.2024.
//

#include "include/RayTracer.h"
#include "include/Scene/Sphere.h"
#include "include/Camera/Camera.h"
#include "include/Scene/IntersectableList.h"

// ! Now unused. Moved to its own folder with Intersectable related code
//double sphere_intersection (const Vec3& center, const double radius, const Ray& r)
//{
//    // A, B, C as in y = Ax^2 + Bx + C
//
//    Vec3 origin_to_center = center - r.origin();
//
//    double A = r.direction().len_squared();
//    // OLD: double B = dot_prod(r.direction(), origin_to_center) * -2.0;
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
//        return -1.0;
//    }
//    else
//    {
//        // OLD: return (-B - sqrt(dlt)) / (2.0 * A);
//        return (H - sqrt(dlt)) / A;
//    }
//}

int main()
{
	// World
	IntersectableList scene;

	scene.add (std::make_shared <Sphere> (Vec3(0, 0, -1), 0.5));
	scene.add (std::make_shared <Sphere> (Vec3(0, -100.5, -1), 100));

	// Camera
	Camera cam;

	cam.init   ();
	cam.render (scene);

    return 0;
}
