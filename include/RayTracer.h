//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <cmath>
#include <random>
#include <limits>
#include <iostream>
#include <bits/shared_ptr.h>


const double INF = std::numeric_limits <double> ::infinity();
const double PI = 3.1415926535897932384626433832795028841971;


inline double rand_double ()
{
	// Modern c++ is great
	static std::mt19937 generator;
	static std::uniform_real_distribution <double> distribution (0.0, 1.0);
	return distribution (generator);
}

inline double rand_double (double min, double max)
{
	// Minimum value + the given range * 0 - 1 (Giving a part of the range)
	return min + rand_double() * (max - min);
}

inline double deg_to_rad (double deg)
{
	return deg * (PI / 180);
}


#include "Rendering/Color.h"
#include "Math/Range.h"
#include "Rendering/Ray.h"
#include "Math/Vec3.h"


#endif //RAYTRACER_RAYTRACER_H
