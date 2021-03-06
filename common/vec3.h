#pragma once
#define _USE_MATH_DEFINES
#include<cmath>
#undef _USE_MATH_DEFINES

#include <iostream>

class Vec3 final {
public:
	Vec3() = default;
	Vec3(const Vec3&) = default;
	Vec3(Vec3&&) = default;
	~Vec3() = default;
	Vec3& operator=(const Vec3&) = default;
	Vec3& operator=(Vec3&&) = default;

	explicit Vec3(const float a) :_x(a), _y(a), _z(a) {}
	Vec3(const float x, const float y, const float z):_x(x), _y(y), _z(z) {}

	float x() const { return _x;}
	float y() const { return _y; }
	float z() const { return _z; }

	float r() const { return _x; }
	float g() const { return _y; }
	float b() const { return _z; }

	Vec3 const& operator +()const { return *this; }
	Vec3 operator - ()const { return{ -_x, -_y, -_z }; }

	Vec3& operator +=(const Vec3& v) { _x += v._x, _y += v._y; _z += v._z; return *this;}
	Vec3& operator -=(const Vec3& v) { _x -= v._x, _y -= v._y, _z -= v._z; return *this; }
	Vec3& operator *=(const Vec3& v) { _x *= v._x, _y *= v._y, _z *= v._z; return *this; }
	Vec3& operator /=(const Vec3& v) { _x /= v._x, _y /= v._y, _z /= v._z; return *this; }
	
	Vec3& operator +=(const float s) { _x += s; _y += s; _z += s; return *this; }
	Vec3& operator -=(const float s) { _x -= s; _y -= s; _z -= s; return *this; }
	Vec3& operator *=(const float s) { _x *= s; _y *= s; _z *= s; return *this; }
	Vec3& operator /=(const float s) { _x /= s; _y /= s; _z /= s; return *this; }

private:
	float _x, _y, _z;
};

inline Vec3 operator +(const Vec3& left, const Vec3& right) { return Vec3(left) += right; }
inline Vec3 operator -(const Vec3& left, const Vec3& right) { return Vec3(left) -= right; }
inline Vec3 operator *(const Vec3& left, const Vec3& right) { return Vec3(left) *= right; }
inline Vec3 operator /(const Vec3& left, const Vec3& right) { return Vec3(left) /= right; }

inline Vec3 operator +(const Vec3& left, const float right) { return Vec3(left) += right; }
inline Vec3 operator -(const Vec3& left, const float right) { return Vec3(left) -= right; }
inline Vec3 operator *(const Vec3& left, const float right) { return Vec3(left) *= right; }
inline Vec3 operator /(const Vec3& left, const float right) { const float f = 1.f / right;  return Vec3(left) *= f; }

inline Vec3 operator + (const float left, const Vec3& right) { return { left + right.x(), left + right.y(), left + right.z() }; }
inline Vec3 operator - (const float left, const Vec3& right) { return { left - right.x(), left - right.y(), left - right.z() }; }
inline Vec3 operator * (const float left, const Vec3& right) { return { left * right.x(), left * right.y(), left * right.z() }; }
inline Vec3 operator / (const float left, const Vec3& right) { return { left / right.x(), left / right.y(), left / right.z() }; }

inline float Dot(const Vec3& l, const Vec3& r) {
	return l.x() * r.x() + l.y() * r.y() + l.z() * r.z();
}

inline Vec3 Cross(const Vec3& l, const Vec3& r) {
	return Vec3{
		l.y() * r.z() - l.z() * r.y(),
		l.z() * r.x() - l.x() * r.z(),
		l.x() * r.y() - l.y() * r.x()
	};
}

inline float SquaredLength(const Vec3& v) { 
	return Dot(v, v); 
}

inline float Length(const Vec3& v) { 
	return std::sqrt(SquaredLength(v)); 
}

inline Vec3 Sqrt(const Vec3& v){
	return { std::sqrt(v.x()), std::sqrt(v.y()), std::sqrt(v.z()) };
}

inline Vec3 UniVector(const Vec3& v) {
	return v / Length(v);
}

inline std::istream& operator >>(std::istream& in, Vec3 v) {
	float x, y, z;
	in >> x >> y >> z;
	v = Vec3(x, y, z);
	return in;
}

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
	return out << v.x() << " " << v.y() << " " << v.z();
}