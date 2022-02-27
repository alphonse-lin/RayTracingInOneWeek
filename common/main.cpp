#include "Vec3.h"
#include "Ray.h"

#include <fstream>
#include <string>

#include <iostream>

const Vec3f Sky(const Ray& ray);
bool Hit_Sphere(const Vec3f& center, float raidus, const Ray& ray);
const Vec3f Trace(const Ray& ray);

int main() {

	//Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int width = 200;
	//const int height = static_cast<int>(width / aspect_ratio);
	const int height = 100;

	//Camera
	Vec3f pos(0.f);
	Vec3f lowerLeft(-2, -1, -1);
	Vec3f horizontal(4, 0, 0);
	Vec3f vertical(0, 2, 0);

	//Export
	//const std::string ROOT_PATH();
	std::ofstream rst("data/04.ppm");

	//Render

	rst << "P3\n" << width << ' ' << height << "\n256\n";

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			float u = float(i) / float(width);
			float v = float(height - j) / float(height);

			Vec3f dir = lowerLeft + u * horizontal + v * vertical - pos;
			Ray ray(pos, dir);

			auto color = Trace(ray);

			Vec3f iSkyColor = 255.99f * color;
			rst << iSkyColor.r << " " << iSkyColor.g << " " << iSkyColor.b << std::endl;
		}
	}

	rst.close();
	std::cout << "finished" << std::endl;
	return 0;
}

const Vec3f Sky(const Ray& ray) {
	auto normDir = ray.d.Normalize();
	float t = 0.5f * (normDir.y + 1.0f);// 将法向的范围映射到 [0, 1] 以可视化

	const Vec3f white(1.f);
	const Vec3f blue(0.5, 0.7, 1);

	return Vec3f::Lerp(white, blue, t);//线性插值
}

bool Hit_Sphere(const Vec3f& center, float radius, const Ray& ray) {
	// c : center
	// r : radius
	// o : ray.o
	// d : ray.d
	// 
	// o + t * d == p
	// (p-c)^2 == r^2
	// (d * t + o - c)^2 == r^2
	// d*d * t^2 + 2*d*(o-c) * t + (o-c)^2 - r^2 = 0

	auto oc = ray.o - center;
	float a = ray.d.Dot(ray.d);
	float b = 2.f * ray.d.Dot(oc);
	float c = oc.Dot(oc) - radius * radius;

	float delta = b * b - 4.f * a * c;
	if (delta < 0.f)
		return false;
	
	return true;
}

const Vec3f Trace(const Ray& ray) {
	if (Hit_Sphere({ 0, 0, -1 }, 0.5f, ray))
		return {1, 0, 0};
	return Sky(ray);
}