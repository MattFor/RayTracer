//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


#include "../Math/Range.h"
#include "../Math/Vec3.h"

class Color : public Vec3 {
public:
    using Vec3::Vec3;
    Color (Vec3 v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
    };

    static void display (std::ostream&, const Color&);
};


#endif //RAYTRACER_COLOR_H
