//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Math/Vec3.h"

double Vec3::len () const
{
	return sqrt(this->len_squared());
}

double Vec3::len_squared () const
{
	return this->x*this->x + this->y*this->y + this->z*this->z;
}