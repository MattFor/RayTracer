//
// Created by MattFor on 14.04.2024.
//

#ifndef RAYTRACER_INTERSECTABLELIST_H
#define RAYTRACER_INTERSECTABLELIST_H


#include <vector>

#include "Intersectable.h"

class IntersectableList : public Intersectable {
public:
    IntersectableList () {};
    IntersectableList (std::shared_ptr <Intersectable> intersectable)
    {
        this->add(intersectable);
    };

	std::vector <std::shared_ptr<Intersectable>> contents {};

    void add (std::shared_ptr <Intersectable> intersectable);
	void remove (std::shared_ptr <Intersectable> intersectable);

	bool hit (const Ray&, double ray_smin, double ray_smax, IntersectionInfo& info) const override;
};


#endif //RAYTRACER_INTERSECTABLELIST_H
