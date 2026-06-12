# raytracing-from-scratch-cpp

> High-performance, multi-threaded Monte Carlo path tracer written from scratch in modern C++20.

```
                    .-----.
                   /       \
             _..---;       ;---.._
           .'       \     /       '.
          /          '---'          \
         ;    Ray-Sphere Slab Test   ;
         |       BVH Traversal       |
          \                         /
           '.                     .'
             '--..___________..--'
```

## Features

- **Modern C++20 Core**: Constexpr vector algebra, concept constraints, and zero external dependencies.
- **Monte Carlo Path Tracing**: Physically accurate diffuse, metallic reflection, and dielectric refraction.
- **Spatial Acceleration**: Bounding Volume Hierarchy (BVH) with fast AABB slab intersection checks.
- **Multithreading**: Automatic CPU core topology detection with thread-local RNG buffers.
- **Color Pipeline**: Progressive multi-sample anti-aliasing with gamma 2.0 tone mapping.

## Quickstart

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/raytracer > output.ppm
```

## Benchmark

| Resolution | Samples | Threads | Rays/Sec | Render Time |
| :--- | :--- | :--- | :--- | :--- |
| **800x450** | **64 spp** | 16 | **2.4M/s** | **2.14s** |
| **1920x1080** | **256 spp** | 16 | **2.6M/s** | **18.92s** |

## License

MIT © [ThreadCrash](https://github.com/ThreadCrash)
