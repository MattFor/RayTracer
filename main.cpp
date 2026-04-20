//
// Created by MattFor on 13.04.2024.
//


#include <print>
#include <limits>
#include <iostream>

#include "include/Scene/Scenes.h"
#include "include/Camera/Camera.h"
#include "include/Scene/IntersectableList.h"

int main (const int argc, char** argv)
{
    int choice = 0;

    if ( argc >= 2 )
    {
        errno     = 0;
        char* end = nullptr;

        if ( const long value = std::strtol ( argv[ 1 ], &end, 10 );
            end != argv[ 1 ] && *end == '\0' &&
            errno != ERANGE &&
            value >= std::numeric_limits <int>::min () &&
            value <= std::numeric_limits <int>::max () )
        {
            choice = static_cast <int> ( value );
        }
        else
        {
            std::print ( "Invalid argument!\n" );
            return 1;
        }
    }

    while ( true )
    {
        std::print (
            "\nChoose scene:\n"
            "1 -> Random spheres (default)\n"
            "2 -> Two spheres\n"
            "3 -> Three spheres\n"
            "Any other number -> exit\n"
        );

        if ( argc < 2 )
        {
            if ( !( std::cin >> choice ) )
            {
                std::print ( "Error reading input!\n" );
                return 1;
            }
        }

        IntersectableList scene;
        Camera            cam;

        switch ( choice )
        {
            case 1:
            {
                scene_random_spheres ( scene, cam );
            }
            break;

            case 2:
            {
                scene_two_spheres ( scene, cam );
            }
            break;

            case 3:
            {
                scene_three_spheres ( scene, cam );
            }
            break;

            default:
            {
                std::print ( "Exiting...\n" );
                return 0;
            }
        }

        cam.render ( scene );

        std::system ( "xdg-open ../image_result.ppm &" );

        if ( argc >= 2 )
        {
            return 0;
        }
    }
}