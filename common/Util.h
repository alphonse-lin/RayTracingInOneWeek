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
}

#endif // !_UTIL_H_
