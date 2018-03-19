#include "GameLib\/Framework.h"
#include "GameLib/Math.h"
#include "Vector3D.h"
#include "Matrix44.h"
#include "Matrix34.h"

using namespace GameLib;

//double[4]‚ðƒZƒbƒg
void Matrix44::multiply(double * out, const Vector3D & in) const
{
	out[0] = m00 * in.x + m01 * in.y + m02 * in.z + m03;
	out[1] = m10 * in.x + m11 * in.y + m12 * in.z + m13;
	out[2] = m20 * in.x + m21 * in.y + m22 * in.z + m23;
	out[3] = m30 * in.x + m31 * in.y + m32 * in.z + m33;
}

void Matrix44::setPerspectiveTransform(double fieldOfViewY, double windowWidth, double windowHeight, double nearClip, double farClip)
{
	double s = 1.0 / tan(0.5*fieldOfViewY);
	double r = windowHeight / windowWidth;
	double a = farClip / (nearClip - farClip);
	double b = nearClip*a;
	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m30 = m31 = m33 =0.0;
	m00 = s*r;
	m11 = s;
	m22 = a;
	m23 = b;
	m32 = -1.0;
}

void Matrix44::setMul(const Matrix44& m_44, const Matrix34& m_34)
{
	double tx, ty, tz;

	tx = m_44.m00; ty = m_44.m01; tz = m_44.m02;
	m00 = tx * m_34.m00 + ty * m_34.m10 + tz * m_34.m20;
	m01 = tx * m_34.m01 + ty * m_34.m11 + tz * m_34.m21;
	m02 = tx * m_34.m02 + ty * m_34.m12 + tz * m_34.m22;
	m03 = tx * m_34.m03 + ty * m_34.m13 + tz * m_34.m23 + m_44.m03;
	tx = m_44.m10; ty = m_44.m11; tz = m_44.m12;
	m10 = tx * m_34.m00 + ty * m_34.m10 + tz * m_34.m20;
	m11 = tx * m_34.m01 + ty * m_34.m11 + tz * m_34.m21;
	m12 = tx * m_34.m02 + ty * m_34.m12 + tz * m_34.m22;
	m13 = tx * m_34.m03 + ty * m_34.m13 + tz * m_34.m23 + m_44.m13;
	tx = m_44.m20; ty = m_44.m21; tz = m_44.m22;
	m20 = tx * m_34.m00 + ty * m_34.m10 + tz * m_34.m20;
	m21 = tx * m_34.m01 + ty * m_34.m11 + tz * m_34.m21;
	m22 = tx * m_34.m02 + ty * m_34.m12 + tz * m_34.m22;
	m23 = tx * m_34.m03 + ty * m_34.m13 + tz * m_34.m23 + m_44.m23;

	tx = m_44.m30; ty = m_44.m31; tz = m_44.m32;
	m30 = tx * m_34.m00 + ty * m_34.m10 + tz * m_34.m20;
	m31 = tx * m_34.m01 + ty * m_34.m11 + tz * m_34.m21;
	m32 = tx * m_34.m02 + ty * m_34.m12 + tz * m_34.m22;
	m33 = tx * m_34.m03 + ty * m_34.m13 + tz * m_34.m23 + m_44.m33;

}

void Matrix44::operator*=(const Matrix34 & m)
{
	setMul(*this, m);
}
