#include "Vec3.h"
#include <fstream>
#include <string>


int main() {

	//Image

	const int width = 200;
	const int height = 100;

	//Export
	//const std::string ROOT_PATH();
	std::ofstream rst("data/02.ppm");

	//Render

	rst << "P3\n" << width << ' ' << height << "\n256\n";

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			float r = float(i) / float(width);
			float g = float(height - j) / float(height);
			float b = 0.2f;

			Vec3f color(r, g, b);
			
			Vec3i icolor = 255.99f * color;
			rst << icolor.r << " " << icolor.g << " " << icolor.b << std::endl;
		}
	}

	rst.close();
	return 0;
}