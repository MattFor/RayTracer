//
// Created by MattFor on 20/04/2026.
//

#ifndef RAYTRACER_BVH_H
#define RAYTRACER_BVH_H

#include <memory>
#include <vector>

#include "Intersectable.h"

class BVHNode : public Intersectable
{
public:
    BVHNode (std::vector <std::shared_ptr <Intersectable>>& objects, int start, int end);

    bool hit (const Ray&, Range, IntersectionInfo&) const override;
    AABB bounding_box() const override;
private:
    AABB box;

    std::shared_ptr <Intersectable> left;
    std::shared_ptr <Intersectable> right;
};

#endif //RAYTRACER_BVH_H