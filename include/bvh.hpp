
// update 1: perf(bvh): implement SAH (Surface Area Heuristic) for optimal split planes [2026-08-01T11:12:00+03:00]

// update 2: refactor(simd): align AABB min/max bounds to 32-byte cacheline boundaries [2026-08-05T11:51:00+03:00]

// update 3: feat(camera): add configurable aperture and focal distance for depth of field [2026-08-09T13:29:00+03:00]

// update 4: perf(render): vectorize ray-box intersection with AVX2 _mm256_fmadd_ps [2026-08-13T16:37:00+03:00]

// update 5: fix(dielectric): handle total internal reflection edge case at critical angle [2026-08-17T17:21:00+03:00]

// update 6: chore(benchmark): add automated headless rendering speed test harness [2026-08-21T12:23:00+03:00]
