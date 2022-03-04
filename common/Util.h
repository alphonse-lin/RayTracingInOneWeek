#ifndef _UTIL_H_

#define _UTIL_H_
#include "Vec3.h"
#include <random>

//用于获取CPU核心数
#ifdef WIN32
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

// 用一个命名空间来便利查找接口
namespace Util {
	constexpr float PI = 3.1415926f;
	constexpr float LARGE_FLT = 98e8f; // 大浮点数
	constexpr float DELTA_FLT = 98e-8f; // 小浮点数
	constexpr float DEFAULT_TMIN = 0.001f;

	// [0, 1)
	float RandF() {
		static std::default_random_engine engine;
		static std::uniform_real_distribution<float> fMap(0.0f, 1.f - DELTA_FLT);
		return fMap(engine);
	}

	// [0, 1)
	const Vec3f RandInSphere() {
		Vec3f p;
		do {
			p = 2.0 * Vec3f(RandF(), RandF(), RandF()) - Vec3f(1.f);
		} while (p.Norm2() >= 1.f);
		return p.Normalize();
	}

	const Vec3f Gamma(const Vec3f &color) {
		float x = std::pow(color.x, 1.f / 2.2f);
		float y = std::pow(color.y, 1.f / 2.2f);
		float z = std::pow(color.z, 1.f / 2.2f);
		return { x,y,z };
	}
}

#endif // !_UTIL_H_
