//
// Created by MattFor on 13.04.2024.
//

#include "../../include/Rendering/Ray.h"

const Vec3& Ray::origin () const
{
	return this->_origin;
}

const Vec3& Ray::direction () const
{
	return this->_direction;
}

Vec3 Ray::pos_at (double s) const
{
	return this->_origin + s * this->_direction;
}
