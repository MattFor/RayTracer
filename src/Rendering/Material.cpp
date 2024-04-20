//
// Created by MattFor on 15.04.2024.
//

#include "../../include/Rendering/Material.h"

bool Material::scatter_light (const Ray& r_in, const IntersectionInfo&, Color& attenuation, Ray& scattered) const
{
	return false;
}

bool Lambertian::scatter_light (const Ray& r_in, const IntersectionInfo& info, Color& attenuation, Ray& scattered) const
{
	Vec3 scatter_dir = info.norm + rand_unit_on_hemisphere();

	if (scatter_dir.near_zero())
	{
		scatter_dir = info.norm;
	}

	scattered = Ray(info.i_point, scatter_dir);
	attenuation = this->albedo;
	return true;
}

bool Metal::scatter_light (const Ray& r_in, const IntersectionInfo& info, Color& attenuation, Ray& scattered) const
{
	Vec3 reflection = smooth_reflect(r_in.direction(), info.norm);
	reflection      = unit_vec(reflection) + (this->fuzz * rand_unit_on_hemisphere());
	// No need to check if its near zero since it will always deflect according to the linear formula
	scattered       = Ray(info.i_point, reflection);
	attenuation     = this->albedo;
	return dot_prod(scattered.direction(), info.norm) > 0.0;
}

bool Dielectric::scatter_light (const Ray& r_in, const IntersectionInfo& info, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);
	double c_refr_index = info.orientation ? (1.0 / this->refr_index) : this->refr_index;

	Vec3 unit_dir = unit_vec(r_in.direction());
	double cos_theta = std::fmin(dot_prod(-unit_dir, info.norm), 1);
	double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

	bool uncorrectable = c_refr_index * sin_theta > 1.0;

	Vec3 dir = uncorrectable || this->reflectance(cos_theta, c_refr_index) > rand_double() ?
			smooth_reflect(unit_dir, info.norm) :
		    refract(unit_dir, info.norm, c_refr_index);

	scattered = Ray(info.i_point, dir);
	return true;
}

double Dielectric::reflectance (double cos, double refr_index)
{
	double r0 = (1.0 - refr_index) / (1.0 + refr_index);
	r0 = r0*r0;
	return std::pow(1.0 - cos, 5.0) * (1.0 - r0) + r0;
}
