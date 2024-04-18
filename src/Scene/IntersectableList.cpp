//
// Created by MattFor on 14.04.2024.
//

#include <chrono>

#include "../../include/Scene/IntersectableList.h"

void IntersectableList::clear()
{
	this->contents.clear();
}

void IntersectableList::add (std::shared_ptr <Intersectable> intersectable)
{
    this->contents.push_back(intersectable);
}

void IntersectableList::remove (std::shared_ptr<Intersectable> intersectable)
{
	this->contents.erase(
			std::remove_if (
					this->contents.begin(),
					this->contents.end(),
					[&] (const std::shared_ptr <Intersectable> correct_obj)
					{
						return intersectable = correct_obj;
					}),
					this->contents.end()
			);
}

bool IntersectableList::hit (const Ray& r, Range ray_s, IntersectionInfo &info) const
{
	IntersectionInfo temp_info;

	double closest = ray_s.max;

	for (const std::shared_ptr <Intersectable>& intersectable : this->contents)
	{
		if (intersectable->hit(r, Range(ray_s.min, closest), temp_info))
		{
			info = temp_info;
			closest = temp_info.s;

			return true;
		}
	}

	return false;
}
