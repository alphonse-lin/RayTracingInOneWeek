#include "Sphere.h"
#include "HitableList.h"

#include <fstream>
#include <string>

#include <iostream>
#include<ctime>

const double CLOCKS_PER_MILLISECOND = ((clock_t)1);

const Vec3f Sky(const Ray& ray);
const Vec3f Trace(Ptr<Hitable> scene, Ray& ray);

int main() {
	
	clock_t startTime, endTime;
	startTime = clock();
	//Image
	//auto aspect_ratio = 16.0 / 9.0;
	int width = 200;
	//const int height = static_cast<int>(width / aspect_ratio);
	int height = 100;
	int sampleNum = 100;

	//Camera
	Vec3f pos(0.f);
	Vec3f lowerLeft(-2, -1, -1);
	Vec3f horizontal(4, 0, 0);
	Vec3f vertical(0, 2, 0);

	//Scene
	auto sphere = Sphere::New({ 0, 0, -1 }, 0.5f);
	auto ground = Sphere::New({ 0, -100.5, -1 }, 100.f);
	auto scene = HitableList::New({ sphere, ground });

	//Export
	//const std::string ROOT_PATH();
	std::ofstream rst("data/07.ppm");

	//Render

	rst << "P3\n" << width <<" " << height << "\n255\n";

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			Vec3f color(0.f);
			for (int k = 0; k < sampleNum; k++)//multiple sampling
			{
				float u = (i + Util::RandF()) / width;
				float v = (height - j + Util::RandF()) / height;

				Vec3f dir = lowerLeft + u * horizontal + v * vertical - pos;
				Ray ray(pos, dir);
				color += Trace(scene, ray);
			}
			color /= float(sampleNum);
			Vec3f gammaColor = Util::Gamma(color);

			Vec3f iSkyColor = 255.99f * gammaColor;
			rst << iSkyColor.r << " " << iSkyColor.g << " " << iSkyColor.b << std::endl;
		}
	}

	rst.close();
	endTime = clock();
	std::cout << (double)((endTime - startTime) / CLOCKS_PER_MILLISECOND)/1000 << "s" << std::endl;
	std::cout << "finished" << std::endl;
	return 0;
}

const Vec3f Sky(const Ray& ray) {
	auto normDir = ray.d.Normalize();
	float t = 0.5f * (normDir.y + 1.0f);// map normal into 0-1 to vis

	const Vec3f white(1.f);
	const Vec3f blue(0.5, 0.7, 1);

	return Vec3f::Lerp(white, blue, t);//linear lerp
}

const Vec3f Trace(Ptr<Hitable> scene, Ray & ray) {
	HitRecord rec;
	if (scene->Hit(ray, rec))
	{
		Vec3f dir = rec.n + Util::RandInSphere();//diffuse
		Ray newRay(rec.p, dir.Normalize());
		return 0.5f * Trace(scene, newRay);//decay half
	}
	return Sky(ray);
}