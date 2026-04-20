//
// Created by MattFor on 14.04.2024.
//

#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <random>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "../../include/Camera/Camera.h"

namespace
{
    thread_local uint64_t rng_state = [] ()
    {
        const auto tid = std::hash <std::thread::id> {} ( std::this_thread::get_id () );
        return 0x9E3779B97F4A7C15ull ^ tid;
    } ();

    uint64_t xorshift64 ()
    {
        rng_state ^= rng_state << 13;
        rng_state ^= rng_state >> 7;
        rng_state ^= rng_state << 17;
        return rng_state;
    }

    double rand_double_thread_local (const double min = 0.0, const double max = 1.0)
    {
        return ( xorshift64 () >> 11 ) * ( 1.0 / ( 1ULL << 53 ) ) * ( max - min ) + min;
    }

    Vec3 rand_in_unit_disk_thread_local ()
    {
        while ( true )
        {
            const Vec3 p (
                rand_double_thread_local ( -1.0, 1.0 ),
                rand_double_thread_local ( -1.0, 1.0 ),
                0.0
            );

            if ( p.len_squared () < 1.0 )
            {
                return p;
            }
        }
    }
}


// Public
void Camera::render (const Intersectable& scene)
{
    this->init ();

    const auto start = std::chrono::steady_clock::now ();

    std::vector <Color> framebuffer (
        static_cast <std::size_t> ( this->img_width ) * static_cast <std::size_t> ( this->img_height )
    );

    // Tile-based scheduling for better cache behaviour
    constexpr int tile_size   = 32;
    const int     tiles_x     = ( this->img_width + tile_size - 1 ) / tile_size;
    const int     tiles_y     = ( this->img_height + tile_size - 1 ) / tile_size;
    const int     total_tiles = tiles_x * tiles_y;

    {
        std::atomic next_tile { 0 };

        const unsigned thread_count = std::max ( 1u, std::thread::hardware_concurrency () );

        std::vector <std::jthread> workers;
        workers.reserve ( thread_count );

        for ( unsigned t = 0; t < thread_count; ++t )
        {
            workers.emplace_back ( [this, &scene, &framebuffer, &next_tile, tiles_x, tiles_y, tile_size, total_tiles](std::stop_token st)
            {
                while ( true )
                {
                    constexpr int chunk = 4;
                    const int s = next_tile.fetch_add ( chunk );

                    if (s >= total_tiles)
                    {
                        break;
                    }

                    for ( int tile = s; tile < s + chunk; ++tile )
                    {
                        if ( tile >= total_tiles )
                        {
                            break;
                        }

                        const int tile_y = tile / tiles_x;
                        const int tile_x = tile % tiles_x;

                        const int y0 = tile_y * tile_size;
                        const int x0 = tile_x * tile_size;
                        const int y1 = std::min ( y0 + tile_size, this->img_height );
                        const int x1 = std::min ( x0 + tile_size, this->img_width );

                        for ( int i = y0; i < y1; ++i )
                        {
                            for ( int j = x0; j < x1; ++j )
                            {
                                Color pix_clr ( 0.0, 0.0, 0.0 );

                                for ( int k = 0; k < this->samp_per_pix; ++k )
                                {
                                    Ray r   = this->get_ray ( i, j );
                                    pix_clr += ray_clr ( r, this->max_ray_depth, scene );
                                }

                                framebuffer[ static_cast <std::size_t> ( i ) * static_cast <std::size_t> ( this->img_width ) + static_cast <std::size_t> ( j ) ] = Color ( this->pix_samp_scale * pix_clr );
                            }
                        }
                    }
                }
            } );
        }
    }

    std::ofstream out ( "../image_result.ppm" );

    out << "P3\n" << this->img_width << ' ' << this->img_height << "\n255\n";

    for ( int i = 0; i < this->img_height; ++i )
    {
        for ( int j = 0; j < this->img_width; ++j )
        {
            const std::size_t idx = static_cast <std::size_t> ( i ) * static_cast <std::size_t> ( this->img_width ) + static_cast <std::size_t> ( j );
            Color::display ( out, framebuffer[ idx ] );
        }
    }

    const std::chrono::duration <double> render_time = std::chrono::steady_clock::now () - start;
    std::clog << "Output complete. Render time: " << render_time.count () << " seconds\n";
}

void Camera::init ()
{
    this->img_height = static_cast <int> ( this->img_width / this->aspect_ratio );
    this->img_height = this->img_height < 1.0 ? 1.0 : this->img_height;

    this->cam_center     = this->cam_origin;
    this->pix_samp_scale = 1.0 / this->samp_per_pix;

    this->w = unit_vec ( this->cam_origin - this->cam_facing_point );
    this->u = unit_vec ( cross_prod ( this->v_up, this->w ) );
    this->v = cross_prod ( this->w, this->u );

    const double theta           = deg_to_rad ( this->vert_fov );
    const double h               = std::tan ( theta / 2.0 );
    const double viewport_height = 2.0 * h * this->focus_dist;
    const double viewport_width  = viewport_height * static_cast <double> ( this->img_width ) / this->img_height;

    // Calculate vectors across horizontal and vertical viewport edges
    const Vec3 viewport_u = viewport_width * this->u;
    const Vec3 viewport_v = viewport_height * -this->v;

    // Calculate vertical and horizontal pixel deltas
    this->pix_dlt_u = viewport_u / this->img_width;
    this->pix_dlt_v = viewport_v / this->img_height;

    // Calculate location of top left pixel
    const Vec3 viewport_top_left = this->cam_center - this->focus_dist * this->w - viewport_u / 2.0 - viewport_v / 2.0;
    this->pix_sp_loc             = viewport_top_left + ( this->pix_dlt_u + this->pix_dlt_v ) * 0.5;

    const double defocus_radius = this->focus_dist * std::tan ( deg_to_rad ( this->defocus_ang / 2.0 ) );
    this->defocus_disk_u        = u * defocus_radius;
    this->defocus_disk_v        = v * defocus_radius;
}

// Private
Vec3 Camera::samp_square ()
{
    return Vec3 (
        rand_double_thread_local ( -0.5, 0.5 ),
        rand_double_thread_local ( -0.5, 0.5 ),
        0.0
    );
}

Vec3 Camera::defocus_disk_samp () const
{
    const Vec3 point = rand_in_unit_disk_thread_local ();
    return this->cam_center + point.x * this->defocus_disk_u + ( point.y * this->defocus_disk_v );
}

Ray Camera::get_ray (const int height, const int width) const
{
    const Vec3 offset = this->samp_square ();

    const Vec3 pix_samp = this->pix_sp_loc +
                          ( static_cast <double> ( height ) + offset.y ) * this->pix_dlt_v +
                          ( static_cast <double> ( width ) + offset.x ) * this->pix_dlt_u;

    const Vec3 ray_origin    = this->defocus_ang <= 0.0 ? this->cam_center : this->defocus_disk_samp ();
    const Vec3 ray_direction = pix_samp - ray_origin;

    return Ray ( ray_origin, ray_direction );
}

Color Camera::ray_clr (const Ray& r, const int depth, const Intersectable& scene)
{
    if ( depth <= 0 )
    {
        return Color ( 0.0, 0.0, 0.0 );
    }

    // Added 0.001 instead of 0 to guard against floating point imprecision
    if ( IntersectionInfo info; scene.hit ( r, Range ( 0.0001, infinity ), info ) )
    {
        Color attenuation;

        if ( Ray scattered; info.mat->scatter_light ( r, info, attenuation, scattered ) )
        {
            return attenuation * ray_clr ( scattered, depth - 1, scene );
        }

        return Color ( 0.0, 0.0, 0.0 );
    }

    const Vec3   unit_dir = unit_vec ( r.direction () );
    const double A        = ( unit_dir.y + 1.0 ) * 0.5;

    return ( 1.0 - A ) * Color { 1.0, 1.0, 1.0 } + A * Color ( 0.5, 0.7, 1.0 );
}