#ifndef _VEC3_H_
#define _VEC3_H_

#include <cassert>
#include <cmath>
#include <algorithm>
#include <type_traits>

template<typename T>
class Vec3;
using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;

template<typename T>
class Vec3 {
public:
	template<typename T1, typename T2, typename T3>
	Vec3(T1 x, T2 y, T3 z) :
		x(static_cast<T>(x)),
		y(static_cast<T>(y)),
		z(static_cast<T>(z)) 
	{
		assert(!HasNaN());
	}

	// 该模板函数如果不正确使用，IDE 不报错，编译期才会报出大量的编译错误提示
	// 而且该函数非常容易就错误使用了
	// 因此我们使用 std::enable_if 使其在错误使用时隐藏起来
	template<typename U, typename=typename std::enble_if<std::is_convertible<U,T>::value>::type>
	Vec3(U, V) :Vec3(static_cast<T>(v), static_cast<T>(v), static_cast<T>(v)){}
	Vec3() :Vec3(0) {}

	template<typename U>
	Vec3(const Vec3<U>& v) : Vec3(v.x, v.y, v.z) {}

public:
	//异常检测
	bool HasNan() const {
		return std::isnan(static_cast<float>(x))
			|| std::isnan(static_cast<float>(y))
			|| std::isnan(static_cast<float>(z));
	}

	//最值
	static const Vec3 Min() {

	}
};
#endif // !_VEC3_H_
