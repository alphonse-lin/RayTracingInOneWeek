#ifndef _UTIL_H_

#define _UTIL_H_
#include "Vec3.h"
#include <random>

//���ڻ�ȡCPU������
#ifdef WIN32
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#endif

// ��һ�������ռ����������ҽӿ�
namespace Util {
	constexpr float PI = 3.1415926f;
	constexpr float LARGE_FLT = 98e8f; // �󸡵���
	constexpr float DELTA_FLT = 98e-8f; // С������
	constexpr float DEFAULT_TMIN = 0.001f;
}

#endif // !_UTIL_H_
