//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "Intersectable.h"

class Sphere : public Intersectable {
public:
    Sphere (const Vec3& center, double radius) : center(center), radius(fmax(0, radius)) {};
    bool hit (const Ray&, Range, IntersectionInfo&) const override;

private:
    Vec3 center;
    double radius;
};


#endif //RAYTRACER_SPHERE_H
