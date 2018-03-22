#include "..\include\Matrix33.h"
#include "Matrix34.h"
#include "Vector3D.h"
#include "GameLib\Framework.h"
using namespace GameLib;
void Matrix33::setReduction(const Matrix34 & m)
{
	m00 = m.m00; m01 = m.m01; m02 = m.m02;
	m10 = m.m00; m11 = m.m11; m12 = m.m12;
	m20 = m.m20; m21 = m.m21; m22 = m.m22;

}

void Matrix33::setReductionInverse(const Matrix34 & m)
{
	double e[3][3];
	double a[3][3];
	a[0][0] = m.m00;a[0][1] = m.m01;a[0][2] = m.m02;
	a[1][0] = m.m10; a[1][1] = m.m11; a[1][2] = m.m12;
	a[2][0] = m.m20; a[2][1] = m.m21; a[2][2] = m.m22;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			e[i][j] = j == i ? 1 : 0;
		}
	}

	//‘|‚«o‚µ–@
	double pivot = 0.0;
	for (int k = 0; k < 3; ++k) {
		pivot = a[k][k];

		a[k][k] = k == 2 && pivot == 0 ? 0.0 : 1.0;

		for (int i = k + 1; i < 3; ++i) {
			a[k][i] /= pivot;
		}
		for (int i = 0; i <= k; ++i) {
			e[k][i] /= pivot;
		}

		for (int i = k + 1; i < 3; ++i) {

			for (int j = 0; j <= k; ++j) {
				e[i][j] -= e[k][j] * a[i][k];
			}
			for (int j = k + 1; j < 3; ++j) {
				a[i][j] -= a[k][j] * a[i][k];
			}
			a[i][k] = 0.0;
		}

	}

	for (int k = 2; k >= 0; --k) {
		for (int i = k - 1; i >= 0; --i) {
			for (int j = 2; j >= 0; --j) {
				e[i][j] -= a[i][k] * e[k][j];
			}
		}
	}

	m00 = e[0][0]; m01 = e[0][1]; m02 = e[0][2];
	m10 = e[1][0]; m11 = e[1][1]; m12 = e[1][2];
	m20 = e[2][0]; m21 = e[2][1]; m22 = e[2][2];

}

void Matrix33::setReductionTransInverse(const Matrix34 & m)
{
	double e[3][3];
	double a[3][3];
	a[0][0] = m.m00; a[0][1] = m.m01; a[0][2] = m.m02;
	a[1][0] = m.m10; a[1][1] = m.m11; a[1][2] = m.m12;
	a[2][0] = m.m20; a[2][1] = m.m21; a[2][2] = m.m22;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			e[i][j] = j == i ? 1 : 0;
		}
	}
	//‘|‚«o‚µ–@
	double pivot = 0.0;
	for (int k = 0; k < 3; ++k) {
		pivot = a[k][k];

		a[k][k] = k == 2 && pivot == 0 ? 0.0 : 1.0;

		for (int i = k + 1; i < 3; ++i) {
			a[k][i] /= pivot;
		}
		for (int i = 0; i <= k; ++i) {
			e[k][i] /= pivot;
		}

		for (int i = k + 1; i < 3; ++i) {

			for (int j = 0; j <= k; ++j) {
				e[i][j] -= e[k][j] * a[i][k];
			}
			for (int j = k + 1; j < 3; ++j) {
				a[i][j] -= a[k][j] * a[i][k];
			}
			a[i][k] = 0.0;
		}

	}

	for (int k = 2; k >= 0; --k) {
		for (int i = k - 1; i >= 0; --i) {
			for (int j = 2; j >= 0; --j) {
				e[i][j] -= a[i][k] * e[k][j];
			}
		}
	}
	m00 = e[0][0]; m01 = e[1][0]; m02 = e[2][0];
	m10 = e[0][1]; m11 = e[1][1]; m12 = e[2][1];
	m20 = e[0][2]; m21 = e[1][2]; m22 = e[2][2];

}

void Matrix33::multiply(Vector3D * out, const Vector3D & in) const
{
	double tmpX = in.x;
	double tmpY = in.y;
	
	out->x = m00 * tmpX + m01 * tmpY + m02 * in.z;
	out->y = m10 * tmpX + m11 * tmpY + m12 * in.z;
	out->z = m20 * tmpX + m21 * tmpY + m22 * in.z;

}
