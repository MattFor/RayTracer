//
// Created by MattFor on 13.04.2024.
//
// P(s) = A + sB
//
// When going from point A to point B linearly.
//
// Where
// - P is a position along a 3D line.
// - A is the origin point of the ray.
// - s is the scalar value used to traverse along the ray.

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H


#include "Vec3.h"

class Ray {
public:
    Ray () = default;
    Ray (const Vec3& origin, const Vec3& direction) : _original(origin), _direction(direction) {};

    [[nodiscard]] const Vec3& origin() const  { return this->_original; }
    [[nodiscard]] const Vec3& direction() const { return this->_direction; }

    [[nodiscard]] Vec3 pos_at(double s) const
    {
        return this->_original + s * this->_direction;
    }

private:
    Vec3 _direction;
    Vec3 _original;
};


#endif //RAYTRACER_RAY_H