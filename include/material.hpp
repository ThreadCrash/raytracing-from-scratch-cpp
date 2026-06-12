#pragma once
#include "hittable.hpp"
#include <random>

inline float random_float() {
    static thread_local std::mt19937 generator(1337);
    static thread_local std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

inline Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 p(random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f, random_float() * 2.0f - 1.0f);
        if (p.length_squared() >= 1.0f) continue;
        return p;
    }
}

class Material {
public:
    virtual ~Material() = default;
    virtual bool scatter(
        const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
    ) const = 0;
};

class Lambertian : public Material {
public:
    Color albedo;
    explicit Lambertian(const Color& a) : albedo(a) {}

    bool scatter(const Ray&, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        Vec3 scatter_direction = rec.normal + unit_vector(random_in_unit_sphere());
        if (scatter_direction.length_squared() < 1e-8f)
            scatter_direction = rec.normal;
        scattered = Ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }
};

class Metal : public Material {
public:
    Color albedo;
    float fuzz;

    Metal(const Color& a, float f) : albedo(a), fuzz(f < 1.0f ? f : 1.0f) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
        Vec3 reflected = r_in.direction - 2.0f * dot(r_in.direction, rec.normal) * rec.normal;
        scattered = Ray(rec.p, unit_vector(reflected) + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction, rec.normal) > 0);
    }
};
