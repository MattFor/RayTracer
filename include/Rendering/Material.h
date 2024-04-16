//
// Created by MattFor on 15.04.2024.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H


#include "../RayTracer.h"
#include "../Scene/Intersectable.h"

class Material {
public:
	virtual ~Material () = default;
	virtual bool scatter_light (const Ray& r_in, const IntersectionInfo&, Color& attenuation, Ray& scattered) const;
};

class Lambertian : public Material {
public:
	Lambertian (const Color& albedo) : albedo(albedo) {};
	bool scatter_light (const Ray& r_in, const IntersectionInfo&, Color& attenuation, Ray& scattered) const;

private:
	Color albedo;
};

class Metal : public Material {
public:
	Metal (const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {};
	bool scatter_light (const Ray& r_in, const IntersectionInfo&, Color& attenuation, Ray& scattered) const;

private:
	double fuzz;
	Color albedo;
};

// Material that light can pass through f.e glass
class Dielectric : public Material {
public:
	Dielectric (double refr_index) : refr_index(refr_index) {}
	bool scatter_light (const Ray& r_in, const IntersectionInfo&, Color& attenuation, Ray& scattered) const;

private:
	// Refractive index in vacuum or air
	// The ratio of the material's refractive index over the refractive index of the enclosing media
	double refr_index;
	static double reflectance (double cos, double refr_index);
};


#endif //RAYTRACER_MATERIAL_H
