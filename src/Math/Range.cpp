//
// Created by MattFor on 14.04.2024.
//

#include "../../include/Math/Range.h"

const Range Range::full = Range (-INF, +INF);
const Range Range::empty = Range (+INF, -INF);

double Range::size () const
{
	return this->max - this->min;
}

double Range::has (double x) const
{
	return this->min <= x && x <= this->max;
}

double Range::clamp (double x) const
{
	if (x > this->max)
	{
		return this->max;
	}

	if (x < this->min)
	{
		return this->min;
	}

	return x;
}

double Range::surrounds (double x) const
{
	return this->min < x && x < this->max;
}
