#ifndef _SPHERE_H_

#include"Hitable.h"

class Sphere :public Hitable {
public:
	Sphere(const Vec3f& center, float radius, Ptr<Material> material)
		:center(center), radius(radius), material(material) {}

public:
	//����Ptr�ı����ӿ�
	static Ptr<Sphere> New(const Vec3f& center, float radius, Ptr<Material> material = nullptr) {
		return std::make_shared<Sphere>(center, radius, material);
	}


public:
	virtual bool Hit(Ray& ray, HitRecord& rec) const override;
	//virtual const Box GetBox()

public:
	Vec3f center;
	float radius;
	Ptr<Material> material;
};

bool Sphere::Hit(Ray& ray, HitRecord& rec) const {
	// o + t * d == p
	// (p-c)^2 == r^2
	// (d * t + o - c)^2 == r^2
	// d*d * t^2 + 2*d*(o-c) * t + (o-c)^2 - r^2 = 0
	auto oc = ray.o - center;
	float a = ray.d.Dot(ray.d);
	float b = ray.d.Dot(oc);
	float c = oc.Dot(oc) - radius * radius;

	float discriminant = b * b - a * c;
	if (discriminant < 0.f)
		return false;

	float sqrtDistriminant = sqrt(discriminant);

	float t0 = (-b - sqrtDistriminant) / a;//��С��
	if (t0 <= ray.tMin || t0 >= ray.tMax) {
		float t1 = (-b + sqrtDistriminant) / a;//�ϴ��
		if (t1 <= ray.tMin || t1 >= ray.tMax)
			return false;//������tMin��tMax֮��

		ray.tMax = t1;//����tMax
	}
	else {
		ray.tMax = t0;//����tMax
	}
	rec.p = ray.EndPos();
	rec.n = (rec.p - center) / radius;

	rec.material = material;

	return true;
}
#endif // !_SPHERE_H_
