//
// Created by MattFor on 13.04.2024.
//

#include "../../include/SceneObjects/Intersectable.h"

void IntersectionInfo::get_normal_orientation (const Ray& r, const Vec3& normal)
{
    this->orientation = dot_prod(r.direction(), normal) < 0;
    this->norm = this->orientation ? normal : -normal;
}
