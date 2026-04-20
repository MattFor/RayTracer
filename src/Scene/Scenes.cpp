//
// Created by MattFor on 20/04/2026.
//

#include "../../include/Scene/Scenes.h"
#include "../../include/Scene/Sphere.h"
#include "../../include/Rendering/Material.h"

void scene_random_spheres (IntersectableList& scene, Camera& cam)
{
    auto ground_material = std::make_shared <Lambertian> ( Color ( 0.5, 0.5, 0.5 ) );

    scene.add ( std::make_shared <Sphere> ( Vec3 ( 0, -1000, 0 ), 1000, ground_material ) );

    for ( int a = -11; a < 11; a++ )
    {
        for ( int b = -11; b < 11; b++ )
        {
            const double choose_mat = rand_double ();

            Vec3 center (
                a + 0.9 * rand_double (),
                0.2 + 0.2 * rand_double (),
                b + 0.9 * rand_double ()
            );

            if ( ( center - Vec3 ( 4, 0.2, 0 ) ).len () > 0.9 )
            {
                std::shared_ptr <Material> sphere_material;

                if ( choose_mat < 0.8 )
                {
                    Color albedo    = Color::rand () * Color::rand ();
                    sphere_material = std::make_shared <Lambertian> ( albedo );
                }
                else if ( choose_mat < 0.95 )
                {
                    Color  albedo   = Color::rand ( 0.5, 1 );
                    double fuzz     = rand_double ( 0, 0.5 );
                    sphere_material = std::make_shared <Metal> ( albedo, fuzz );
                }
                else
                {
                    sphere_material = std::make_shared <Dielectric> ( 1.5 );
                }

                scene.add ( std::make_shared <Sphere> ( center, 0.2, sphere_material ) );
            }
        }
    }

    auto mat1 = std::make_shared <Dielectric> ( 1.5 );
    auto mat2 = std::make_shared <Lambertian> ( Color ( 0.4, 0.2, 0.1 ) );
    auto mat3 = std::make_shared <Metal> ( Color ( 0.7, 0.6, 0.5 ), 0.0 );

    scene.add ( std::make_shared <Sphere> ( Vec3 ( 2, 1, 0 ), 1.0, mat1 ) );
    scene.add ( std::make_shared <Sphere> ( Vec3 ( -4, 1, 2 ), 1.0, mat2 ) );
    scene.add ( std::make_shared <Sphere> ( Vec3 ( 4, 1, -2 ), 1.0, mat3 ) );

    scene.build_bvh ();

    // Camera
    cam.aspect_ratio  = 16.0 / 9.0;
    cam.img_width     = 1080;
    cam.samp_per_pix  = 10;
    cam.max_ray_depth = 20;

    cam.vert_fov         = 20;
    cam.cam_origin       = Vec3 ( 13, 2, 3 );
    cam.cam_facing_point = Vec3 ( 0, 0, 0 );
    cam.v_up             = Vec3 ( 0, 1, 0 );

    cam.defocus_ang = 0.3;
    cam.focus_dist  = 10.0;
}


void scene_three_spheres (IntersectableList& scene, Camera& cam)
{
    auto mat_ground = std::make_shared <Lambertian> ( Color ( 0.8, 0.8, 0.0 ) );
    auto mat_center = std::make_shared <Lambertian> ( Color ( 0.1, 0.2, 0.5 ) );
    auto mat_left   = std::make_shared <Dielectric> ( 1.5 );
    auto mat_right  = std::make_shared <Metal> ( Color ( 0.8, 0.6, 0.2 ), 0.0 );

    scene.add ( std::make_shared <Sphere> ( Vec3 ( 0, -100.5, -1 ), 100, mat_ground ) );
    scene.add ( std::make_shared <Sphere> ( Vec3 ( 0, 0, -1 ), 0.5, mat_center ) );
    scene.add ( std::make_shared <Sphere> ( Vec3 ( -1, 0, -1 ), 0.5, mat_left ) );
    scene.add ( std::make_shared <Sphere> ( Vec3 ( 1, 0, -1 ), 0.5, mat_right ) );

    scene.build_bvh ();

    cam.aspect_ratio  = 16.0 / 9.0;
    cam.img_width     = 800;
    cam.samp_per_pix  = 20;
    cam.max_ray_depth = 10;

    cam.vert_fov         = 40;
    cam.cam_origin       = Vec3 ( 3, 3, 2 );
    cam.cam_facing_point = Vec3 ( 0, 0, -1 );
    cam.v_up             = Vec3 ( 0, 1, 0 );

    cam.defocus_ang = 0.0;
    cam.focus_dist  = ( cam.cam_origin - cam.cam_facing_point ).len ();
}

void scene_two_spheres (IntersectableList& scene, Camera& cam)
{
    auto mat = std::make_shared <Lambertian> ( Color ( 0.8, 0.3, 0.3 ) );

    scene.add ( std::make_shared <Sphere> ( Vec3 ( 0, 0, -1 ), 0.5, mat ) );
    scene.add ( std::make_shared <Sphere> ( Vec3 ( 0, -100.5, -1 ), 100, mat ) );

    scene.build_bvh ();

    cam.aspect_ratio  = 16.0 / 9.0;
    cam.img_width     = 600;
    cam.samp_per_pix  = 10;
    cam.max_ray_depth = 5;

    cam.vert_fov         = 60;
    cam.cam_origin       = Vec3 ( 0, 0, 0 );
    cam.cam_facing_point = Vec3 ( 0, 0, -1 );
    cam.v_up             = Vec3 ( 0, 1, 0 );

    cam.defocus_ang = 0.0;
    cam.focus_dist  = 1.0;
}