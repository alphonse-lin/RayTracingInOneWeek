#pragma once
#include "Vec3.h"
#include <random>

typedef std::mt19937 Random;

inline float Unitform(Random& random) {
	return std::uniform_real_distribution<float>()(random);
}

inline Vec3 RandomInUnitDisk(Random& random) {
	for (;;) {
		const Vec3 p = 2 * Vec3(Unitform(random), Unitform(random), 0) - Vec3(1, 1, 0);
		if (SquaredLength(p)<1)
		{
			return p;
		}
	}
}

inline Vec3 RandomInUnitSphere(Random& random) {
	for (;;) {
		const Vec3 p = 2 * Vec3(Unitform(random), Unitform(random), Unitform(random)) - 1;
		if (SquaredLength(p)<1)
		{
			return p;
		}
	}
}

