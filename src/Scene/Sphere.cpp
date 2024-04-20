//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Scene/Sphere.h"

bool Sphere::hit (const Ray& r, Range ray_s, IntersectionInfo& info) const
{
    Vec3 origin_to_center = this->center - r.origin();

    double A = r.direction().len_squared();
    // OLD: double B = dot_prod(r.direction(), origin_to_center) * -2;
    double H = dot_prod(r.direction(), origin_to_center);
    double C = origin_to_center.len_squared() - radius*radius;

    // Δ > 0 - 2 intersection points
    // Δ == 0 - 1 intersection point
    // Δ < 0 - 0 intersection points
    //
    // OLD: double dlt = B*B - 4*A*C;
    // Changed because:
    // - vector dotted with itself is just the length of itself squared
    // - the equation simplifies if "-2H" is substituted for "B"
    //
    // Currently moved from main.cpp due to better Intersectable management.
    double dlt = H*H - A*C;

    if (dlt < 0.0)
    {
        return false;
    }

    double dlt_sqrt = std::sqrt(dlt);
    double intersect_point = (H - dlt_sqrt) / A;

    // Find intersection point which lies within the acceptable range
    if (!ray_s.surrounds(intersect_point))
    {
        intersect_point = (H + dlt_sqrt) / A;
        if (!ray_s.surrounds(intersect_point))
        {
            return false;
        }
    }

    info.s = intersect_point;
    info.i_point = r.pos_at(info.s);
	Vec3 outward_norm = (info.i_point - this->center) / this->radius;
    info.set_normal_orientation(r, outward_norm);
	info.mat = this->mat;

    return true;
}
