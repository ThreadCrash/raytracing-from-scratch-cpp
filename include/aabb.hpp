#pragma once
#include "ray.hpp"
#include <algorithm>

struct AABB {
    Point3 min_b;
    Point3 max_b;

    constexpr AABB() = default;
    constexpr AABB(const Point3& a, const Point3& b) : min_b(a), max_b(b) {}

    [[nodiscard]] bool hit(const Ray& r, float t_min, float t_max) const {
        for (int a = 0; a < 3; ++a) {
            float invD = 1.0f / (&r.direction.x)[a];
            float t0 = ((&min_b.x)[a] - (&r.origin.x)[a]) * invD;
            float t1 = ((&max_b.x)[a] - (&r.origin.x)[a]) * invD;
            if (invD < 0.0f) std::swap(t0, t1);
            t_min = t0 > t_min ? t0 : t_min;
            t_max = t1 < t_max ? t1 : t_max;
            if (t_max <= t_min) return false;
        }
        return true;
    }
};
