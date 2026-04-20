//
// Created by MattFor on 14.04.2024.
//

#include <chrono>

#include "../../include/Scene/IntersectableList.h"

void IntersectableList::build_bvh ()
{
    if ( this->contents.empty () )
    {
        return;
    }

    this->contents = { std::make_shared <BVHNode> ( this->contents, 0, static_cast <int> ( this->contents.size () ) ) };
}

[[maybe_unused]] void IntersectableList::clear ()
{
    this->contents.clear ();
}

[[maybe_unused]] void IntersectableList::remove (std::shared_ptr <Intersectable> intersectable)
{
    std::erase_if (
        this->contents,
        [&](const std::shared_ptr <Intersectable>& correct_obj)
        {
            return intersectable == correct_obj;
        } );
}

void IntersectableList::add (std::shared_ptr <Intersectable> intersectable)
{
    this->contents.push_back ( intersectable );
}

bool IntersectableList::hit (const Ray& r, const Range ray_s, IntersectionInfo& info) const
{
    IntersectionInfo temp_info;
    double           closest               = ray_s.max;
    bool             intersection_detected = false;

    for ( const std::shared_ptr <Intersectable>& intersectable : this->contents )
    {
        if ( intersectable->hit ( r, Range ( ray_s.min, closest ), temp_info ) )
        {
            info                  = temp_info;
            closest               = temp_info.s;
            intersection_detected = true;
        }
    }

    return intersection_detected;
}

AABB IntersectableList::bounding_box() const
{
    if (contents.empty())
        return AABB();

    AABB temp = contents[0]->bounding_box();

    for (size_t i = 1; i < contents.size(); ++i)
    {
        temp = surrounding_box(temp, contents[i]->bounding_box());
    }

    return temp;
}