cmake_minimum_required(VERSION 3.27)
project(RayTracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(RayTracer main.cpp
        src/Basics/Vec3.cpp
        include/Basics/Vec3.h
        src/Basics/Color.cpp
        include/Basics/Color.h
        src/Basics/Ray.cpp
        include/Basics/Ray.h
        src/Basics/Intersectable.cpp
        include/Basics/Intersectable.h
        src/SceneObjects/Sphere.cpp
        include/SceneObjects/Sphere.h)
