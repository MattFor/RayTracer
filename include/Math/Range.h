//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_RANGE_H
#define RAYTRACER_RANGE_H


#include "../RayTracer.h"

class Range {
public:
	Range () : min(+INF), max(-INF) {};
	Range (double min, double max) : min(min), max(max) {};

	double min;
	double max;

	double size () const;
	double has (double) const;
	double clamp (double) const;
	double surrounds (double) const;

	static const Range full;
	static const Range empty;
};


#endif //RAYTRACER_RANGE_H
