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
		y = 15. * PI / 180., 
		p = 15. * PI / 180., 
		r = 15. * PI / 180.;
	double fov = 90.;
	double far = 1000., near = 1.;

	Trans << 1, 0, 0, 0,
			 0, 1, 0, 0,
			 0, 0, 1, 1000,
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

	Raster <<	1. / tan(fov * PI / 180 / 2), 0, 0, 0,
				0, 1. / tan(fov * PI / 180 / 2), 0, 0,
				0, 0, - (far + near) / (far - near), -(2. * far * near) / (far - near),
				0, 0, 1, 0;
	
	unsigned char* Render;
	int render_w = 1000, render_h = 1000;
	Render = new unsigned char[render_h * render_w * 3];

	for (int i = 0; i < render_w * render_h * 3; i++) Render[i] = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int x_p = x - width / 2;
			int y_p = y - width / 2;
			Vector4d cod, trns;
			cod << x_p, y_p, 0, 1;
			trns = Raster * Trans * Yaw * Roll * Pitch * cod;
			trns /= trns(3);

			int x_t = (trns(0) * render_w) + (render_w / 2.);
			int y_t = (trns(1) * render_h) + (render_h / 2.);

			if (x_t >= render_w || y_t >= render_h || x_t < 0 || y_t < 0) continue;
			Render[(x_t + (y_t * render_w)) * 3 + 0] = img[(x + (y * width)) * 3 + 0];
			Render[(x_t + (y_t * render_w)) * 3 + 1] = img[(x + (y * width)) * 3 + 1];
			Render[(x_t + (y_t * render_w)) * 3 + 2] = img[(x + (y * width)) * 3 + 2];
		}
	}
	WriteBmp((char*)"Render.BMP", Render, render_w, render_h);

	y = -30. * PI / 180.,
	p = -30. * PI / 180.,
	r = 0 * PI / 180.;
	fov = 103.;
	far = 1000., near = 1.;

	Trans << 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 1000,
		0, 0, 0, 1;

	Yaw << cos(y), 0, sin(y), 0,
		0, 1, 0, 0,
		-sin(y), 0, cos(y), 0,
		0, 0, 0, 1;

	Pitch << 1, 0, 0, 0,
		0, cos(p), -sin(p), 0,
		0, sin(p), cos(p), 0,
		0, 0, 0, 1;

	Roll << cos(r), -sin(r), 0, 0,
		sin(r), cos(r), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	Raster << 1. / tan(fov * PI / 180 / 2), 0, 0, 0,
		0, 1. / tan(fov * PI / 180 / 2), 0, 0,
		0, 0, -(far + near) / (far - near), -(2. * far * near) / (far - near),
		0, 0, 1, 0;

	for (int i = 0; i < render_w * render_h * 3; i++) Render[i] = 0;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int x_p = x - width / 2;
			int y_p = y - width / 2;
			Vector4d cod, trns;
			cod << x_p, y_p, 0, 1;
			trns = Raster * Trans * Yaw * Roll * Pitch * cod;
			trns /= trns(3);

			int x_t = (trns(0) * render_w) + (render_w / 2.);
			int y_t = (trns(1) * render_h) + (render_h / 2.);

			if (x_t >= render_w || y_t >= render_h || x_t < 0 || y_t < 0) continue;
			Render[(x_t + (y_t * render_w)) * 3 + 0] = img[(x + (y * width)) * 3 + 0];
			Render[(x_t + (y_t * render_w)) * 3 + 1] = img[(x + (y * width)) * 3 + 1];
			Render[(x_t + (y_t * render_w)) * 3 + 2] = img[(x + (y * width)) * 3 + 2];
		}
	}
	WriteBmp((char*)"Render2.BMP", Render, render_w, render_h);

	delete[] Render, img;
	return 0;
}