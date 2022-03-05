#ifndef _METAL_H_
#define _METAL_H_

#include "Material.h"
#include "Util.h"

class Metal :public Material {
public:
	Metal(const Vec3f & albedo, float fuzz):albedo(albedo), fuzz(fuzz){}
	
public:
	static Ptr<Metal> New(const Vec3f& albedo, float fuzz = 0.f) {
		return std::make_shared<Metal>(albedo, fuzz);
	}

public:
	virtual const ScatterRst Scatter(const Ray& ray, const HitRecord& rec) const override;

public:
	Vec3f albedo;
	float fuzz;
};

const ScatterRst Metal::Scatter() {

}

#endif // !_METAL_H_
