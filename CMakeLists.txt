cmake_minimum_required(VERSION 3.20)
project(RayTracerScratch VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /O2 /arch:AVX2 /fp:fast)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3 -march=native -ffast-math)
endif()

include_directories(include)

add_executable(raytracer
    src/main.cpp
)

find_package(Threads REQUIRED)
target_link_libraries(raytracer PRIVATE Threads::Threads)
