//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "../Basics/Intersectable.h"

class Sphere : Intersectable {
public:
    Sphere (const Vec3& center, double radius) : center(center), radius(fmax(0, radius)) {};
    bool hit (const Ray&, double ray_smin, double ray_smax, IntersectionInfo&) const override;

private:
    Vec3 center;
    double radius;
};


#endif //RAYTRACER_SPHERE_H
