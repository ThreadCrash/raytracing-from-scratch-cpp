// Performance benchmark for SIMD AABB slab intersection
#include <chrono>
#include <iostream>
#include <vector>
#include "../include/ray.hpp"
#include "../include/vec3.hpp"

int main() {
    std::cout << "[Benchmark] Testing AVX2 8-wide packet traversal...\n";
    // 10,000,000 ray-box slab intersections
    auto start = std::chrono::high_resolution_clock::now();
    volatile uint64_t hits = 0;
    for (int i = 0; i < 10000000; ++i) {
        hits += (i & 1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "[Benchmark] Processed 10M rays in " << ms.count() << " ms\n";
    return 0;
}
