#pragma once
#include "vec3.hpp"

struct Ray {
    Point3 origin;
    Vec3 direction;

    constexpr Ray() = default;
    constexpr Ray(const Point3& origin, const Vec3& direction)
        : origin(origin), direction(direction) {}

    [[nodiscard]] constexpr Point3 at(float t) const {
        return origin + t * direction;
    }
};
