//
// Created by MattFor on 20/04/2026.
//

#include "../../include/Scene/BVH.h"

#include <thread>

thread_local uint64_t rng_state = [] ()
{
    const auto tid = std::hash <std::thread::id> {} ( std::this_thread::get_id () );
    return 0x9E3779B97F4A7C15ull ^ tid;
} ();

uint64_t xorshift64 ()
{
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return rng_state;
}

double rand_double_thread_local (const double min = 0.0, const double max = 1.0)
{
    return ( xorshift64 () >> 11 ) * ( 1.0 / ( 1ULL << 53 ) ) * ( max - min ) + min;
}
BVHNode::BVHNode(std::vector<std::shared_ptr<Intersectable>>& objects, int start, int end)
{
    int axis = static_cast<int>(rand_double_thread_local(0, 3));

    auto comparator = [axis](const std::shared_ptr<Intersectable>& a,
                             const std::shared_ptr<Intersectable>& b)
    {
        const AABB boxA = a->bounding_box();
        const AABB boxB = b->bounding_box();

        return boxA.minimum[axis] < boxB.minimum[axis];
    };

    int object_span = end - start;

    if (object_span == 1)
    {
        left = right = objects[start];
    }
    else if (object_span == 2)
    {
        if (comparator(objects[start], objects[start+1]))
        {
            left = objects[start];
            right = objects[start+1];
        }
        else
        {
            left = objects[start+1];
            right = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        int mid = start + object_span / 2;

        left = std::make_shared<BVHNode>(objects, start, mid);
        right = std::make_shared<BVHNode>(objects, mid, end);
    }

    box = surrounding_box(left->bounding_box(), right->bounding_box());

    if (!std::isfinite(box.minimum.x) || !std::isfinite(box.maximum.x))
    {
        throw std::runtime_error("Invalid BVH bounding box");
    }
}

bool BVHNode::hit(const Ray& r, const Range ray_s, IntersectionInfo& info) const
{
    if (!box.hit(r, ray_s))
        return false;

    IntersectionInfo left_info, right_info;

    bool hit_left = left->hit(r, ray_s, left_info);
    bool hit_right = false;

    if (hit_left)
    {
        hit_right = right->hit(r, Range(ray_s.min, left_info.s), right_info);
    }
    else
    {
        hit_right = right->hit(r, ray_s, right_info);
    }

    if (hit_left && hit_right)
    {
        info = (left_info.s < right_info.s) ? left_info : right_info;
        return true;
    }

    if (hit_left)
    {
        info = left_info;
        return true;
    }

    if (hit_right)
    {
        info = right_info;
        return true;
    }

    return false;
}

AABB BVHNode::bounding_box() const
{
    return box;
}