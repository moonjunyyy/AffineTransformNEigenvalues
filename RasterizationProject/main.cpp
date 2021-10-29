#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "bmpNew.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
	unsigned char *img;
	int width, height;
	const double PI = 3.1415926535897932;

	img = ReadBmp((char*)"sunflower.bmp", &width, &height);

	MatrixXd Trans(4,4), Yaw(4, 4), Pitch(4, 4), Roll(4, 4), Raster(4,4);
	double 
		y = 15 * 2 * PI / 180,
		p = 15 * 2 * PI / 180,
		r = 15 * 2 * PI / 180;
	double fov = 90;

	Trans << 1, 0, 0, 0,
			 0, 1, 0, 0,
			 0, 0, 1, 100,
			 0, 0, 0, 1;

	Yaw <<  cos(y), 0, sin(y), 0,
			0,		1, 0,	   0,
		   -sin(y), 0, cos(y), 0,
			0,		0, 0,	   1;

	Pitch << 1, 0,		 0,		 0,
			 0, cos(p), -sin(p), 0,
			 0, sin(p),  cos(p), 0,
			 0, 0,		 0,		 1;

	Roll << cos(r), -sin(r), 0, 0,
			sin(r),  cos(r), 0, 0,
			0,		 0,		 1, 0,
			0,		 0,		 0, 1;

	Raster << 1./tan(fov * 2 * PI / 180),   0, 0, 0,
			  0, 1. / tan(fov * 2 * PI / 180), 0, 0,
			  0, 0, (-1000.+1.)/(-1000. - 1.), (2 * 1000. *1.) / (-1000. - 1.),
			  0, 0, -1, 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int x_p = x - width / 2;
			int y_p = y - width / 2;

		}
	}

	return 0;
}