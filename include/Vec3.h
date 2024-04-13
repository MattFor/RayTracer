//
// Created by MattFor on 13.04.2024.
//

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H


#include <cmath>
#include <ostream>

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
    double z = 0.0;

    Vec3 operator - () const
    {
        return Vec3(-this->x, -this->y, -this->z);
    };

    double operator [] (int i) const
    {
        static const double coords[] = {x, y, z};
        return coords[i];
    };

    double& operator [] (int i)
    {
        static double coords[] = {x, y, z};
        return coords[i];
    };

    Vec3& operator += (const Vec3& v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
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

    [[nodiscard]] double len () const
    {
        return sqrt(this->len_squared());
    };

    [[nodiscard]] double len_squared () const
    {
        return this->x*this->x + this->y*this->y + this->z*this->z;
    };
    double y = 0.0;
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

inline Vec3 cross (const Vec3& u, const Vec3& v)
{
    return Vec3 (u.y*v.z - u.z*v.y,
                 u.z*v.x - u.x*v.z,
                 u.x*v.y - u.y*v.x);
}

inline Vec3 unit_vec (const Vec3& v)
{
    return v / v.len();
}


#endif //RAYTRACER_VEC3_H
