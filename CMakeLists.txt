cmake_minimum_required(VERSION 4.2)

project(RayTracer)

set(CMAKE_CXX_STANDARD 26)

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
        include/RayTracer.h
        include/Scene/BVH.h
        src/Scene/BVH.cpp
        include/Scene/Scenes.h
        src/Scene/Scenes.cpp
        include/Camera/AABB.h)

target_compile_options(RayTracer PRIVATE
        $<$<CONFIG:Release>:-O3>
        $<$<CONFIG:Release>:-DNDEBUG>
        $<$<CONFIG:Release>:-march=native>
        $<$<CONFIG:Release>:-flto>
)

target_link_options(RayTracer PRIVATE
        $<$<CONFIG:Release>:-flto>
)