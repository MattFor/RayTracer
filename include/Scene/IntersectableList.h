//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_INTERSECTABLELIST_H
#define RAYTRACER_INTERSECTABLELIST_H


#include <vector>

#include "BVH.h"
#include "Intersectable.h"

class IntersectableList : public Intersectable
{
public:
    IntersectableList () {};

    explicit IntersectableList (const std::shared_ptr <Intersectable>& intersectable)
    {
        this->add ( intersectable );
    };

    std::vector <std::shared_ptr <Intersectable>> contents {};

    void build_bvh ();

    [[maybe_unused]] void clear ();
    [[maybe_unused]] void remove (std::shared_ptr <Intersectable> intersectable);

    void add (std::shared_ptr <Intersectable> intersectable);
    AABB bounding_box() const override;
    bool hit (const Ray&, Range, IntersectionInfo&) const override;
};


#endif //RAYTRACER_INTERSECTABLELIST_H