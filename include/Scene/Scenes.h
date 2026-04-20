//
// Created by MattFor on 20/04/2026.
//

#ifndef RAYTRACER_SCENES_H
#define RAYTRACER_SCENES_H

#include "IntersectableList.h"
#include "../Camera/Camera.h"

// Each scene builds BOTH scene + camera
void scene_random_spheres(IntersectableList& scene, Camera& cam); // default
void scene_three_spheres(IntersectableList& scene, Camera& cam);
void scene_two_spheres(IntersectableList& scene, Camera& cam);

#endif