//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_INTERSECTABLE_H
#define RAYTRACER_INTERSECTABLE_H


#include "Ray.h"

// Used to note down where rays intersected with an intersectable thing
class IntersectionInfo {
public:
    Vec3 norm;
    Vec3 i_point;
    double s = 0.0;

    bool orientation;

    // Determine whether a normal is facing inwards or outwards from a face
    // Normal here is assumed to have unit length
    void get_normal_orientation (const Ray&, const Vec3&);
};

class Intersectable {
public:
    virtual ~Intersectable () = default;
    virtual bool hit (const Ray&, double ray_smin, double ray_smax, IntersectionInfo& info) const = 0;
};


#endif //RAYTRACER_INTERSECTABLE_H
