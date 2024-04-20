//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H


#include <cmath>
#include <memory>
#include <random>
#include <cstdlib>
#include <iostream>

const double PI = 3.1415926535897932384626433832795028841971;


// inline double rand_double ()
// {
// 	// Modern c++ is great
// 	static std::mt19937 generator;
// 	static std::uniform_real_distribution <double> distribution (0, 1);
// 	return distribution (generator);
// }
//
// inline double rand_double (double min, double max)
// {
// 	// Minimum value + the given range * 0 - 1 (Giving a part of the range)
// 	return min + rand_double() * (max - min);
// }

inline double deg_to_rad (double deg)
{
	return deg * (PI / 180.0);
}


#include "Math/Range.h"
#include "Rendering/Color.h"
#include "Rendering/Ray.h"
#include "Math/Vec3.h"

#endif //RAYTRACER_RAYTRACER_H
