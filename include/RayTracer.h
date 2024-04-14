//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

#include <cmath>
#include <limits>
#include <iostream>
#include <bits/shared_ptr.h>


const double PI = 3.1415926535897932384626433832795028841971;
const double INF = std::numeric_limits <double> ::infinity();


inline double deg_to_rad (double deg)
{
	return deg * (PI / 180);
}

#include "./Basics/Ray.h"
#include "./Basics/Vec3.h"
#include "./Basics/Color.h"

#include "./SceneObjects/Sphere.h"
#include "./SceneObjects//Intersectable.h"
#include "./SceneObjects/IntersectableList.h"

#endif //RAYTRACER_RAYTRACER_H
