//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H


#include <cmath>
#include <random>
#include <ostream>


inline double rand_double ()
{
	// Modern c++ is great
	static std::mt19937 generator;
	static std::uniform_real_distribution <double> distribution (0.0, 1.0);
	return distribution (generator);
}

inline double rand_double (double min, double max)
{
	// Minimum value + the given range * 0 - 1 (Giving a part of the range)
	return min + rand_double() * (max - min);
}

class Vec3 {
public:
    explicit Vec3 () : x(0.0), y(0.0), z(0.0) {};
    explicit Vec3 (double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    };

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    Vec3 operator - () const
    {
        return Vec3(-this->x, -this->y, -this->z);
    };

    double operator [] (int i) const
    {
        static const double coords[] = {this->x, this->y, this->z};
        return coords[i];
    };

    double& operator [] (int i)
    {
        static double coords[] = {this->x, this->y, this->z};
        return coords[i];
    };

    Vec3& operator += (const Vec3& v)
    {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        return *this;
    };

    Vec3& operator *= (double s)
    {
        this->x *= s;
        this->y *= s;
        this->z *= s;
        return *this;
    };

    Vec3& operator /= (double s)
    {
        return *this *= 1/s;
    };

	bool near_zero () const;

    [[nodiscard]] double len () const;
    [[nodiscard]] double len_squared () const;

	static Vec3 rand ();
	static Vec3 rand (double, double);
};

inline std::ostream& operator << (std::ostream& out, const Vec3& v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline Vec3 operator + (const Vec3& u, const Vec3& v)
{
    return Vec3 (u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vec3 operator - (const Vec3& u, const Vec3& v)
{
    return Vec3 (u.x - v.x, u.y - v.y, u.z - v.z);
}

inline Vec3 operator * (const Vec3& u, const Vec3& v)
{
    return Vec3 (u.x * v.x, u.y * v.y, u.z * v.z);
}

inline Vec3 operator * (double s, const Vec3& v)
{
    return Vec3 (v.x * s, v.y * s, v.z * s);
}

inline Vec3 operator * (const Vec3& v, double s)
{
    return s * v;
}

inline Vec3 operator / (const Vec3& v, double s)
{
    return (1 / s) * v;
}

inline double dot_prod (const Vec3& u, const Vec3& v)
{
    return u.x*v.x + u.y*v.y + u.z*v.z;
}

inline Vec3 cross_prod (const Vec3& u, const Vec3& v)
{
    return Vec3 (u.y*v.z - u.z*v.y,
                 u.z*v.x - u.x*v.z,
                 u.x*v.y - u.y*v.x);
}

inline Vec3 unit_vec (const Vec3& v)
{
    return v / v.len();
}

// Return a random vector which fits within a unit sphere
// Reject all others which do not fit the criteria
inline Vec3 rand_in_unit_sphere ()
{
	while (true)
	{
		Vec3 v = Vec3::rand(-1, 1);
		if (v.len_squared() < 1)
		{
			return v;
		}
	}
}

inline Vec3 rand_unit_on_hemisphere ()
{
	return unit_vec(rand_in_unit_sphere());
}

inline Vec3 rand_on_hemisphere (const Vec3& norm)
{
	Vec3 on_unit_sphere = rand_unit_on_hemisphere();

	return dot_prod(on_unit_sphere, norm) > 0.0 ? on_unit_sphere : -on_unit_sphere;
}

inline Vec3 smooth_reflect (const Vec3& u, const Vec3& v)
{
	/**
	 * -- Excerpt directly from the guide --
	 *
	 * n is a unit vector (length one), but v may not be.
	 * To get the vector b, we scale the normal vector by the length of the projection of v onto n, which is given by the dot project v⋅n.
	 * (If n were not a unit vector, we would also need to divide this dot project by the length of n.)
	 * Finally, because v points into the surface, and we want b to point out of the surface, we need to negate this projection length.
	 */
	return u - 2 * dot_prod(u, v) * v;
}

inline Vec3 refract (const Vec3& uv, const Vec3 norm, double refr_index_ratio)
{
	/**
	 * Snell's law implementation
	 *
	 * -- Excerpt directly from the guide --
	 *
	 *  The refraction is described by Snell’s law:
	 *	η ⋅ sinθ =η′⋅ sinθ′
	 *	Where θ and θ′ are the angles from the normal, and η and η′ are the refractive indices.
	 *	In order to determine the direction of the refracted ray, we have to solve for sinθ′
	 *	sinθ′= (η / η′)⋅ sinθ
     *
	 *	On the refracted side of the surface there is a refracted ray R′
	 *	and a normal n′, and there exists an angle, θ′, between them.
	 * 	We can split R′ into the parts of the ray that are perpendicular to n′ and parallel to n′
	 *	R′=R′⊥+R′∥
     *
	 *	If we solve for R′⊥ and R′∥ :
	 *	R′⊥ =(η/η′) * (R+cosθ * n)
	 *	R′∥ =√(1−|R′⊥|2n)
	 *
	 *	We know the value of every term on the right-hand side except for cosθ
	 *
	 *	It is well known that the dot product of two vectors can be explained
	 *	in terms of the cosine of the angle between them:
	 *
	 *	a ⋅ b=|a||b|cosθ
	 *
	 *	If we restrict a and b to be unit vectors:
	 *
	 *	a ⋅ b=cosθ
	 *
	 *	We can now rewrite R′⊥ in terms of known quantities:
	 *	R′⊥=ηη′(R+(−R⋅n)n)
	 *
	 *	When we combine them back together, we can write a function to calculate R′
	 *
	 *	Which finally brings us to this function:
	 */

	double cos_theta    = std::fmin(dot_prod(-uv, norm), 1.0);
	Vec3 r_out_perp     = refr_index_ratio * (uv + cos_theta * norm);
	Vec3 parallel_comp  = -std::sqrt(std::fabs(1.0 - r_out_perp.len_squared())) * norm;
	return r_out_perp + parallel_comp;
}

inline Vec3 rand_in_unit_disk ()
{
	while (true)
	{
		Vec3 point = Vec3 (rand_double(-1, 1), rand_double(-1, 1), 0);
		if (point.len_squared() < 1.0)
		{
			return point;
		}
	}
}


#endif //RAYTRACER_VEC3_H
