cmake_minimum_required(VERSION 3.27)
project(RayTracer)

set(CMAKE_CXX_STANDARD 23)

add_executable(RayTracer main.cpp
        src/Vec3.cpp
        include/Vec3.h
        src/Color.cpp
        include/Color.h)
