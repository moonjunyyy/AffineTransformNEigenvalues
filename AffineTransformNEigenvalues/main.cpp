#include <iostream>
#include <Eigen/Dense>
#include <Eigen/LU>
#include "bmpNew.h"

using namespace std;
using namespace Eigen;

int main(int argc, char* argv[])
{
	//Sprint 1
	MatrixXd Conv(2, 2), iConv;
	Conv << 1, 1,
			1, -3;
	iConv = Conv.inverse();

	//Sprint 2
	unsigned char* imgFlower, * imgConv;
	int width, height;
	imgFlower = ReadBmp((char*)"sunflower.bmp", &width, &height);
	imgConv = new unsigned char[width * height * 3];

	cout << "\n\nC\n" << Conv << endl;
	cout << "\n\niC\n" << iConv << endl;

	cout << width << ", " << height << endl;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			imgConv[(x + (y * width)) * 3 + 0] = 0;
			imgConv[(x + (y * width)) * 3 + 1] = 0;
			imgConv[(x + (y * width)) * 3 + 2] = 0;
		}
	}
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			unsigned char k = x < 10 && y < 10 ? 255 : 0;
			imgConv[(x + (y * width)) * 3 + 0] = k;
			imgConv[(x + (y * width)) * 3 + 1] = k;
			imgConv[(x + (y * width)) * 3 + 2] = k;
		}
	}

	WriteBmp((char*)"sunC.BMP", imgConv, width, height);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			int x_0, y_0;
			Vector2d _XY, XY;
			_XY <<  x - width / 2,
					y - height / 2;
			XY = iConv * _XY;
			x_0 = (int)XY(0, 0) + width / 2;
			y_0 = (int)XY(1, 0) + height / 2;

			bool how = x_0 >= width || x_0 < 0 || y_0 >= height || y_0 < 0;

			//cout << x_0 << ", " << y_0 << endl;
			imgConv[(x + (y * width)) * 3 + 0] = how ? 0 : imgFlower[(x_0 + (y_0 * width)) * 3 + 0];
			imgConv[(x + (y * width)) * 3 + 1] = how ? 0 : imgFlower[(x_0 + (y_0 * width)) * 3 + 1];
			imgConv[(x + (y * width)) * 3 + 2] = how ? 0 : imgFlower[(x_0 + (y_0 * width)) * 3 + 2];
		}
	}

	WriteBmp((char*)"sunConvert.BMP", imgConv, width, height);

	// 1st
	cout << endl << "1ST" << endl << endl;
	MatrixXd A;
	MatrixXd P;
	MatrixXd S;
	MatrixXd PI;
	EigenSolver<MatrixXd> es;

	A.resize(2, 2);
	P.resize(2, 2);
	S.resize(2, 2);
	PI.resize(2, 2);

	A << 1, 2,
		 2, 1;
	es.compute(A);

	cout << "The eigenvalues of A are : " << endl << es.eigenvalues() << endl << es.eigenvectors() << endl;
	for (int i = 0; i < A.rows(); i++) for (int j = 0; j < A.cols(); j++) P(i, j) = es.eigenvectors()(i, j).real();
	cout << "\n\nP\n" << P << endl;

	for (int i = 0; i < A.rows(); i++) S(i, i) = es.eigenvalues()[i].real();
	PI = P.inverse();

	cout << "\n\nA=PSPi\n" << P * S * PI << endl;

	// 2nd
	cout << endl << "2ND" << endl << endl;
	A.resize(2, 2);
	P.resize(2, 2);
	S.resize(2, 2);
	PI.resize(2, 2);

	A << 4, -1,
		2, 1;
	es.compute(A);

	cout << "The eigenvalues of A are : " << endl << es.eigenvalues() << endl;
	for (int i = 0; i < A.rows(); i++) for (int j = 0; j < A.cols(); j++) P(i, j) = es.eigenvectors()(i, j).real();
	cout << "\n\nP\n" << P << endl;

	for (int i = 0; i < A.rows(); i++) S(i, i) = es.eigenvalues()[i].real();
	PI = P.inverse();

	cout << "\n\nA=PSPi\n" << P * S * PI << endl;

	// 3rd
	cout << endl << "3RD" << endl << endl;
	A.resize(2, 2);
	P.resize(2, 2);
	S.resize(2, 2);
	PI.resize(2, 2);

	A << 0, 1,
		-2, -3;
	es.compute(A);

	cout << "The eigenvalues of A are : " << endl << es.eigenvalues() << endl;
	for (int i = 0; i < A.rows(); i++) for (int j = 0; j < A.cols(); j++) P(i, j) = es.eigenvectors()(i, j).real();
	cout << "\n\nP\n" << P << endl;

	for (int i = 0; i < A.rows(); i++) S(i, i) = es.eigenvalues()[i].real();
	PI = P.inverse();

	cout << "\n\nA=PSPi\n" << P * S * PI << endl;


	// 4th
	cout << endl << "4TH" << endl << endl;
	A.resize(3, 3);
	P.resize(3, 3);
	S.resize(3, 3);
	PI.resize(3, 3);

	A << 5, 2, 0,
		 2, 5, 0,
		-3, 4, 6;
	es.compute(A);

	cout << "The eigenvalues of A are : " << endl << es.eigenvalues() << endl;
	for (int i = 0; i < A.rows(); i++) for (int j = 0; j < A.cols(); j++) P(i, j) = es.eigenvectors()(i, j).real();
	cout << "\n\nP\n" << P << endl;

	for (int i = 0; i < A.rows(); i++) S(i, i) = es.eigenvalues()[i].real();
	PI = P.inverse();

	cout << "\n\nA=PSPi\n" << P * S * PI << endl;

	// 5th
	cout << endl << "5TH" << endl << endl;
	A.resize(3, 3);
	P.resize(3, 3);
	S.resize(3, 3);
	PI.resize(3, 3);

	A << 4, -1, 6,
		 2,  1, 6,
		 2, -1, 8;
	es.compute(A);

	cout << "The eigenvalues of A are : " << endl << es.eigenvalues() << endl;
	for (int i = 0; i < A.rows(); i++) for (int j = 0; j < A.cols(); j++) P(i, j) = es.eigenvectors()(i, j).real();
	cout << "\n\nP\n" << P << endl;

	for (int i = 0; i < A.rows(); i++) S(i, i) = es.eigenvalues()[i].real();
	PI = P.inverse();

	cout << "\n\nA=PSPi\n" << P * S * PI << endl;

	return 0;
}