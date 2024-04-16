//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Math/Vec3.h"

bool Vec3::near_zero () const
{
	const double e = 1e-8;
	return (std::fabs(this->x) < e) && (std::fabs(this->y) < e) && (std::fabs(this->z) < e);
}

double Vec3::len () const
{
	return std::sqrt(this->len_squared());
}

double Vec3::len_squared () const
{
	return this->x*this->x + this->y*this->y + this->z*this->z;
}

Vec3 Vec3::rand ()
{
	return Vec3(rand_double(), rand_double(), rand_double());
}

Vec3 Vec3::rand (double a, double b)
{
	return Vec3 (rand_double(a, b), rand_double(a, b), rand_double(a, b));
}
