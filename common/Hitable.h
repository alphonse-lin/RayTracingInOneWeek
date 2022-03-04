#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "Ray.h"
#include "Ptr.h"

class Material;

struct HitRecord {
	//float t; ������Ray�м�¼tMin �� tMax
	Vec3f p;//��ײ��
	Vec3f n;//��λ����
	Ptr< Material> material;
};

class Hitable {
public:
	// ��Ϊ Ray �к��� tMin �� tMax���������ﲻ��Ҫ������Ӧ����
	// ����ཻ���������޸� ray �� tMax
	virtual bool Hit(Ray& ray, HitRecord& rec)const = 0;
};

#endif // !_HITABLE_H_
