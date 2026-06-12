#include "vec3.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

Color ray_color(const Ray& r, const std::vector<std::shared_ptr<Hittable>>& world, int depth) {
    if (depth <= 0) return {0.0f, 0.0f, 0.0f};

    HitRecord rec;
    float closest_so_far = 1e9f;
    bool hit_anything = false;

    for (const auto& object : world) {
        if (object->hit(r, 0.001f, closest_so_far, rec)) {
            hit_anything = true;
            closest_so_far = rec.t;
        }
    }

    if (hit_anything) {
        Ray scattered;
        Color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth - 1);
        return {0.0f, 0.0f, 0.0f};
    }

    Vec3 unit_direction = unit_vector(r.direction);
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Color(1.0f, 1.0f, 1.0f) + t * Color(0.5f, 0.7f, 1.0f);
}

int main() {
    constexpr int image_width = 800;
    constexpr int image_height = 450;
    constexpr int samples_per_pixel = 64;
    constexpr int max_depth = 16;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    std::vector<std::shared_ptr<Hittable>> world;
    world.push_back(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))));
    world.push_back(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, std::make_shared<Lambertian>(Color(0.1, 0.2, 0.5))));
    world.push_back(std::make_shared<Sphere>(Point3(-1, 0, -1), 0.5, std::make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.1)));
    world.push_back(std::make_shared<Sphere>(Point3(1, 0, -1), 0.5, std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0)));

    Point3 origin(0, 0, 0);
    Vec3 horizontal(3.555f, 0, 0);
    Vec3 vertical(0, 2.0f, 0);
    Point3 lower_left_corner = origin - horizontal/2.0f - vertical/2.0f - Vec3(0, 0, 1.0f);

    auto start_time = std::chrono::high_resolution_clock::now();

    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                float u = (i + random_float()) / (image_width - 1);
                float v = (j + random_float()) / (image_height - 1);
                Ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
                pixel_color += ray_color(r, world, max_depth);
            }
            pixel_color /= float(samples_per_pixel);
            // Gamma 2.0 correction
            pixel_color = Color(std::sqrt(pixel_color.x), std::sqrt(pixel_color.y), std::sqrt(pixel_color.z));

            int ir = static_cast<int>(256 * std::clamp(pixel_color.x, 0.0f, 0.999f));
            int ig = static_cast<int>(256 * std::clamp(pixel_color.y, 0.0f, 0.999f));
            int ib = static_cast<int>(256 * std::clamp(pixel_color.z, 0.0f, 0.999f));

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_time - start_time;
    std::cerr << "Render finished in " << diff.count() << " seconds.\n";
    return 0;
}
