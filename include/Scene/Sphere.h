//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include "IntersectableList.h"

class Sphere : public Intersectable {
public:
    Sphere (const Vec3& center, double radius, std::shared_ptr <Material> mat) :
		center(center), radius(std::fmax(0, radius)), mat(mat) {};
	bool hit (const Ray&, Range, IntersectionInfo&) const override;

private:
    Vec3 center;
    double radius;
	std::shared_ptr <Material> mat;
};


#endif //RAYTRACER_SPHERE_H
