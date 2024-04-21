//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Scene/Intersectable.h"

bool Intersectable::hit(const Ray&, Range, IntersectionInfo&) const
{
	return false;
}

void IntersectionInfo::set_norm_orientation (const Ray& r, const Vec3& normal)
{
	this->orientation = dot_prod(r.direction(), normal) < 0.0;
    this->norm = this->orientation ? normal : -normal;
}
