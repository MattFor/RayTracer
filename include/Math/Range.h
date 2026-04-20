//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_RANGE_H
#define RAYTRACER_RANGE_H


#include <limits>

class Range
{
public:
    Range () : min ( +std::numeric_limits <double>::infinity () ),
               max ( -std::numeric_limits <double>::infinity () ) {};

    Range (const double min, const double max) : min ( min ),
                                                 max ( max ) {};

    double min;
    double max;

    [[maybe_unused]] double size () const;
    [[maybe_unused]] double has (double) const;

    double clamp (double) const;
    double surrounds (double) const;
};


#endif //RAYTRACER_RANGE_H