//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_COLOR_H
#define RAYTRACER_COLOR_H


#include "Vec3.h"

class Color : public Vec3 {
public:
    static void display (std::ostream& out, const Color& point_rgb);
};


#endif //RAYTRACER_COLOR_H
