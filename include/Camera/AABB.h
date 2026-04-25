//
// Created by mattfor on 20/04/2026.
//

#ifndef RAYTRACER_AABB_H
#define RAYTRACER_AABB_H

#pragma once
#include "../Rendering/Ray.h"
#include "../Math/Range.h"

struct AABB
{
    Vec3 minimum;
    Vec3 maximum;

    AABB()
        : minimum(std::numeric_limits<double>::infinity(),
                  std::numeric_limits<double>::infinity(),
                  std::numeric_limits<double>::infinity()),
          maximum(-std::numeric_limits<double>::infinity(),
                  -std::numeric_limits<double>::infinity(),
                  -std::numeric_limits<double>::infinity())
    {}

    AABB(const Vec3& a, const Vec3& b) : minimum(a), maximum(b) {}

    bool hit(const Ray& r, Range t) const
    {
        for (int a = 0; a < 3; ++a)
        {
            const double dir = r.direction()[a];
            const double orig = r.origin()[a];

            // Handle near-zero direction (important!)
            if (std::abs(dir) < 1e-8)
            {
                if (orig < minimum[a] || orig > maximum[a])
                    return false;
                continue;
            }

            const double invD = 1.0 / dir;

            double t0 = (minimum[a] - orig) * invD;
            double t1 = (maximum[a] - orig) * invD;

            if (invD < 0.0)
                std::swap(t0, t1);

            t.min = std::max(t.min, t0);
            t.max = std::min(t.max, t1);

            if (t.max < t.min)
                return false;
        }

        return true;
    }


};

inline AABB surrounding_box(const AABB& a, const AABB& b)
{
    Vec3 small(
        std::min(a.minimum.x, b.minimum.x),
        std::min(a.minimum.y, b.minimum.y),
        std::min(a.minimum.z, b.minimum.z));

    Vec3 big(
        std::max(a.maximum.x, b.maximum.x),
        std::max(a.maximum.y, b.maximum.y),
        std::max(a.maximum.z, b.maximum.z));

    return AABB(small, big);
}

#endif //RAYTRACER_AABB_H
