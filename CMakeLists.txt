cmake_minimum_required(VERSION 3.27)

project(RayTracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(RayTracer main.cpp
        src/Rendering/Color.cpp
        include/Rendering/Color.h
        src/Rendering/Ray.cpp
        include/Rendering/Ray.h
        src/Scene/Intersectable.cpp
        src/Scene/Sphere.cpp
        include/Scene/Sphere.h
        src/Scene/IntersectableList.cpp
        include/Scene/IntersectableList.h
        src/Camera/Camera.cpp
        include/Camera/Camera.h
        include/Scene/Intersectable.h
        src/Rendering/Material.cpp
        include/Rendering/Material.h
        src/Math/Range.cpp
        include/Math/Range.h
        src/Math/Vec3.cpp
        include/Math/Vec3.h
        include/RayTracer.h)
