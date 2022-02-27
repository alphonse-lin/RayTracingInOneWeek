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

	// ��ģ�庯���������ȷʹ�ã�IDE �����������ڲŻᱨ�������ı��������ʾ
	// ���Ҹú����ǳ����׾ʹ���ʹ����
	// �������ʹ�� std::enable_if ʹ���ڴ���ʹ��ʱ��������
	template<typename U, typename=typename std::enable_if<std::is_convertible<U,T>::value>::type>
	Vec3(U v) :Vec3(static_cast<T>(v), static_cast<T>(v), static_cast<T>(v)){}
	Vec3() :Vec3(0) {}

	template<typename U>
	Vec3(const Vec3<U>& v) : Vec3(v.x, v.y, v.z) {}

public:
	//�쳣���
	bool HasNaN() const {
		return std::isnan(static_cast<float>(x))
			|| std::isnan(static_cast<float>(y))
			|| std::isnan(static_cast<float>(z));
	}

	//��ֵ
	static const Vec3 Min(const Vec3 & lhs, const Vec3 & rhs) {
		return{ (std::min)(lhs.x, rhs.x), (std::min)(lhs.y, rhs.y),(std::min)(lhs.z, rhs.z) };
	}

	static const Vec3 Max(const Vec3& lhs, const Vec3& rhs) {
		return { (std::max)(lhs.x, rhs.x), (std::max)(lhs.y, rhs.y),(std::max)(lhs.z, rhs.z) };
	}

	//Ԫ�ػ�ȡ
	T & operator[](int n) {
		assert(n >= 0 && n < 3);
		return _data[n];
	}

	const T & operator[](int n)const {
		assert(n >= 0 && n < 3);
		return _data[n];
	}

	//���Բ�ֵ
	template<typename U>
	static const Vec3 Lerp(const Vec3& lhs, const Vec3& rhs, U t) {
		float tF = static_cast<float>(t);
		assert(tF >= 0. && tF <= 1.);
		Vec3f lhsF = lhs;
		Vec3f rhsF = rhs;
		return (1.0f - tF) * lhsF + tF * rhsF;
	}
	template<typename U>
	const Vec3 LerpWith(const Vec3 & rhs, U t) const {
		return Lerp(*this, rhs, t);
	}

	//�������㣺 +, -, *, /
	const Vec3 operator+(const Vec3 & rhs) const {
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vec3& operator+=(const Vec3 & rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	const Vec3 operator-() const{
		return { -x, -y, -z };
	}

	const Vec3 operator-(const Vec3 & rhs) const {
		return{ x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vec3 & operator-=(const Vec3 & rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	const Vec3 operator*(T k)const {
		return { x * k, y * k, z * k };
	}

	Vec3 & operator*=(T k) {
		x *= k;
		y *= k;
		z *= k;
		return *this;
	}

	friend const Vec3 operator*(T k, Vec3 v) {
		return v * k;
	}

	const Vec3 operator/(T k)const {
		assert(k != 0);
		float invK = 1 / k;
		return{ x * invK, y * invK, z * invK };
	}

	Vec3& operator/=(T k) {
		assert(k != 0);
		float invK = 1 / k;
		x *= invK;
		y *= invK;
		z *= invK;
		return *this;
	}

	//�ڻ�
	static T Dot(const Vec3& lhs, const Vec3& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	T Dot(const Vec3& rhs)const {
		return Dot(*this, rhs);
	}

	//�ڻ�����
	T Norm2() const {
		return this->Dot(*this);
	}

	T Norm() const {
		return std::sqrt(Norm2());
	}

	const Vec3 Normalize() const {
		T norm = Norm();
		assert(norm != static_cast<T>(0));
		return *this / norm;
	}

	//��Ԫ�����
	const Vec3 operator*(const Vec3& rhs)const {
		return { x * rhs.x, y * rhs.y, z * rhs.z };
	}

	//���
	static const Vec3 Cross(const Vec3& lhs, const Vec3& rhs) {
		return {
			lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.x * rhs.y - lhs.y * rhs.x
		};
	}
	
	const Vec3 Cross(const Vec3& rhs)const {
		return Cross(*this, rhs);
	}

public:
	union {// ���ü��ɣ�ʹ�����ǿ��Է���Ļ�ȡԪ�أ�������Ҫͨ�������ӿڣ��� x(), y()
		struct { T x, y, z; };
		struct { T r, g, b; };
		struct { T _data[3]; };
	};
};
#endif
