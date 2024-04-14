//
// Created by MattFor on 14.04.2024.
//

#include <chrono>

#include "../../include/SceneObjects/IntersectableList.h"

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

bool IntersectableList::hit (const Ray& r, double ray_smin, double ray_smax, IntersectionInfo &info) const
{
	IntersectionInfo temp_info;

	bool hit_detected = false;
	double closest = ray_smax;

	for (const std::shared_ptr <Intersectable>& intersectable : this->contents)
	{
		if (intersectable->hit(r, ray_smin, closest, temp_info))
		{
			info = temp_info;
			closest = temp_info.s;

			hit_detected = true;
		}
	}

	return hit_detected;
}
