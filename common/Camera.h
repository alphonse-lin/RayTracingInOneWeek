#pragma once
#include "Ray.h"
#include "Random.h"

class Camera final {
public:
	static Camera LookAt(
		const Vec3& origin, const Vec3& target,
		const Vec3& up,
		const float verticalFov, const float aspectRatio,
		const float aperture, const float focusDistance
	) {

	}
};