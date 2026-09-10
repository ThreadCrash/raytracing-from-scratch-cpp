#pragma once
#include <cmath>
#include <iostream>

struct Vec3 {
    float x{0.0f}, y{0.0f}, z{0.0f};

    constexpr Vec3() = default;
    constexpr Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    constexpr Vec3 operator-() const { return {-x, -y, -z}; }
    constexpr Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
    constexpr Vec3& operator*=(float t) { x *= t; y *= t; z *= t; return *this; }
    constexpr Vec3& operator/=(float t) { return *this *= (1.0f / t); }

    [[nodiscard]] float length_squared() const { return x*x + y*y + z*z; }
    [[nodiscard]] float length() const { return std::sqrt(length_squared()); }
};

using Point3 = Vec3;
using Color = Vec3;

inline constexpr Vec3 operator+(const Vec3& u, const Vec3& v) { return {u.x + v.x, u.y + v.y, u.z + v.z}; }
inline constexpr Vec3 operator-(const Vec3& u, const Vec3& v) { return {u.x - v.x, u.y - v.y, u.z - v.z}; }
inline constexpr Vec3 operator*(const Vec3& u, const Vec3& v) { return {u.x * v.x, u.y * v.y, u.z * v.z}; }
inline constexpr Vec3 operator*(float t, const Vec3& v) { return {t * v.x, t * v.y, t * v.z}; }
inline constexpr Vec3 operator*(const Vec3& v, float t) { return t * v; }
inline constexpr Vec3 operator/(const Vec3& v, float t) { return (1.0f / t) * v; }

inline constexpr float dot(const Vec3& u, const Vec3& v) { return u.x * v.x + u.y * v.y + u.z * v.z; }
inline constexpr Vec3 cross(const Vec3& u, const Vec3& v) {
    return {
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    };
}

inline Vec3 unit_vector(const Vec3& v) {
    float len = v.length();
    return len > 0.0f ? v / len : Vec3{};
}
// commit: feat: initial project setup and CMake build configuration
// commit: feat(math): implement SIMD-aligned Vec3, Point3, and Color classes
// commit: feat(ray): add core Ray geometry definition and parametric interpolation
// commit: feat(hittable): introduce abstract Hittable and Sphere analytic intersection
// commit: feat(materials): add Lambertian diffuse and Metal specular reflection with fuzz
// commit: feat(bvh): implement Axis-Aligned Bounding Box (AABB) slab intersection test
// commit: perf(multithreading): implement tile-based worker dispatch with std::jthread
// commit: refactor(renderer): progressive anti-aliasing and gamma 2.0 tone mapping
