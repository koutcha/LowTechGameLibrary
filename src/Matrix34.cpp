#include "Matrix34.h"
#include "Vector3D.h"
#include "GameLib/Math.h"
#include "Quaternion.h"
#include <math.h>
using namespace GameLib;

void Matrix34::multiply(Vector3D * out, const Vector3D & in)const
{
	double tmpX = in.x;
	double tmpY = in.y;
	out->x = m00*tmpX + m01*tmpY + m02*in.z + m03;
	out->y = m10*tmpX + m11*tmpY + m12*in.z + m13;
	out->z = m20*tmpX + m21*tmpY + m22*in.z + m23;
}

void Matrix34::setTranslation(const Vector3D & v)
{
	m00 = m11 = m22 = 1.0;
	m01 = m02 = m10 = m12 = m20 = m21 = 0.0;
	m03 = v.x;
	m13 = v.y;
	m23 = v.z;
}

void Matrix34::setRotationX(double angle)
{
	
	double s = GameLib::sin(angle);
	double c = GameLib::cos(angle);
	m00 = 1.0;
	m01 = m02 = m03 = m10 = m13 = m20 = m23 = 0;
	m11 = c;
	m12 = -s;
	m21 = s;
	m22 = c;

}

void Matrix34::setRotationY(double angle)
{
	
	double s = GameLib::sin(angle);
	double c = GameLib::cos(angle);

	m11 = 1;
	m01 = m03 = m10 = m12 = m13 = m21 = m23 = 0;
	m00 = c;
	m02 = s;
	m20 = -s;
	m22 = c;

}

void Matrix34::setRotationZ(double angle)
{
	double s = GameLib::sin(angle);
	double c = GameLib:: cos(angle);
	m22 = 1;
	m02 = m03 = m12 = m13 = m20 = m21 = m23 = 0;
	m00 = c;
	m01 = -s;
	m10 = s;
	m11 = c;

}

void Matrix34::setScaling(const Vector3D & v)
{
	m01 = m02 = m03 = m10 = m12 = m13 = m20 = m21 = m23 = 0.0;
	m00 = v.x;
	m11 = v.y;
	m22 = v.z;
}

void Matrix34::setViewTransform(const Vector3D & p, const Vector3D & t)
{
	Vector3D d;
	//ÉJÉÅÉâà íuÇ÷à⁄ìÆïœä∑
	d.setSub(t, p);
	double angleX;
	double angleY;
	double xzDistance = GameLib:: sqrt(d.x*d.x + d.z*d.z);

	angleX = GameLib::atan2(d.y, xzDistance);
	angleY = GameLib::atan2(d.x, d.z)+ 180.0;

	
	setRotationX(-angleX);
	rotateY(-angleY);
	translate(Vector3D(-p.x, -p.y, -p.z));

}
double approximately(double value, double checkValue) {
	
	if (fabs(value - checkValue) < 0.0000000001) {
		return checkValue;
	}
	
	return value;
}
void Matrix34::setQuaternionRotaion(const Quaternion& q) {
	Matrix34 m;
	double q1, q2, q3, q0;
	q1 = q.v.x;
	q2 = q.v.y;
	q3 = q.v.z;
	q0 = q.w;
	double q1_2, q2_2, q3_2, q0_2;
	q1_2 = q1*q1;
	q2_2 = q2*q2;
	q3_2 = q3*q3;
	q0_2 = q0*q0;
	//cout << "x" << x << "y" << y << "z" << z << "w" << w << endl;
	m00 = q0_2 + q1_2 - q2_2 - q3_2;
	m01 = 2.0*(q1*q2 - q0*q3);
	m02 = 2.0*(q1*q3 + q0*q2);
	m10 = 2.0*(q1*q2 + q0*q3);
	m11 = q0_2 - q1_2 + q2_2 - q3_2;
	m12 = 2.0*(q2*q3 - q0*q1);
	m20 = 2.0*(q1*q3-q0*q2);
	m21 = 2.0*(q2*q3+q0*q1);
	m22 = q0_2 - q1_2 - q2_2 + q3_2;
	m03 = m13 = m23 = 0;

	double yAngle, xAngle, zAngle;
	
	if (approximately(m21,1.0) == 1.0) {
		xAngle = 90.0;
		yAngle = 0;
		zAngle = GameLib::atan2(m10, m00);
	}
	else if (approximately(m21, -1.0) == -1.0) {
		xAngle = -90.0;
		yAngle = 0;
		zAngle = GameLib::atan2(m10, m00);
	}
	else {
		xAngle = GameLib::asin(-m21);
		yAngle = GameLib::atan2(m20, m22);
		zAngle = GameLib::atan2(m01, m11);
	}
	//setIdentity();
	//rotateY(yAngle);
	//(xAngle);
	//rotateZ(zAngle);
}
void Matrix34::rotateByQuaternion(const Quaternion& q) {
	Matrix34 m;
	m.setQuaternionRotaion(q);
	*this *= m;
}

void Matrix34::translate(const Vector3D & v)
{
	Matrix34 m;
	m.setTranslation(v);
	*this *= m;
}

void Matrix34::rotateX(double angle)
{
	Matrix34 m;
	m.setRotationX(angle);
	*this *= m;
}

void Matrix34::rotateY(double angle)
{
	Matrix34 m;
	m.setRotationY(angle);
	*this *= m;
}

void Matrix34::rotateZ(double angle)
{
	Matrix34 m;
	m.setRotationZ(angle);
	*this *= m;
}



void Matrix34::scale(const Vector3D & v)
{
	Matrix34 m;
	m.setScaling(v);
	*this  *= m;
}

void Matrix34::operator*=(const Matrix34 & m)
{
	double tx, ty, tz;
	//ÇOçsñ⁄
	tx = m00; 
	ty = m01;
	tz = m02;
	m00 = tx*m.m00 + ty*m.m10 + tz*m.m20;
	m01 = tx*m.m01 + ty*m.m11 + tz*m.m21;
	m02 = tx*m.m02 + ty*m.m12 + tz*m.m22;
	m03 = tx*m.m03 + ty*m.m13 + tz*m.m23 + m03;
	//ÇPçsñ⁄
	tx = m10;
	ty = m11;
	tz = m12;
	m10 = tx*m.m00 + ty*m.m10 + tz*m.m20;
	m11 = tx*m.m01 + ty*m.m11 + tz*m.m21;
	m12 = tx*m.m02 + ty*m.m12 + tz*m.m22;
	m13 = tx*m.m03 + ty*m.m13 + tz*m.m23 + m13;
	//ÇQçsñ⁄
	tx = m20;
	ty = m21;
	tz = m22;
	m20 = tx*m.m00 + ty*m.m10 + tz*m.m20;
	m21 = tx*m.m01 + ty*m.m11 + tz*m.m21;
	m22 = tx*m.m02 + ty*m.m12 + tz*m.m22;
	m23 = tx*m.m03 + ty*m.m13 + tz*m.m23 + m23;


}
void Matrix34::setMul(const Matrix34& m1,const Matrix34& m2) {
	double tx, ty, tz;
	//ÇOçsñ⁄
	tx = m1.m00;
	ty = m1.m01;
	tz = m1.m02;
	double sub00, sub01, sub02, sub03;
	sub00 = tx*m2.m00 + ty*m2.m10 + tz*m2.m20;
	sub01 = tx*m2.m01 + ty*m2.m11 + tz*m2.m21;
	sub02 = tx*m2.m02 + ty*m2.m12 + tz*m2.m22;
	sub03 = tx*m2.m03 + ty*m2.m13 + tz*m2.m23 + m1.m03;

	tx = m1.m10;
	ty = m1.m11;
	tz = m1.m12;
	double sub10, sub11, sub12, sub13;
	sub10 = tx*m2.m00 + ty*m2.m10 + tz*m2.m20;
	sub11 = tx*m2.m01 + ty*m2.m11 + tz*m2.m21;
	sub12 = tx*m2.m02 + ty*m2.m12 + tz*m2.m22;
	sub13 = tx*m2.m03 + ty*m2.m13 + tz*m2.m23 + m1.m13;

	tx = m1.m20;
	ty = m1.m21;
	tz = m1.m22;
	double sub20, sub21, sub22;
	sub20 = tx*m2.m00 + ty*m2.m10 + tz*m2.m20;
	sub21 = tx*m2.m01 + ty*m2.m11 + tz*m2.m21;
	sub22 = tx*m2.m02 + ty*m2.m12 + tz*m2.m22;
	m23 = tx*m2.m03 + ty*m2.m13 + tz*m2.m23 + m1.m23;

	m00 = sub00; m01 = sub01; m02 = sub02; m03 = sub03;
	m10 = sub10; m11 = sub11; m12 = sub12; m13 = sub13;
	m20 = sub20; m21 = sub21; m22 = sub22;
}
void Matrix34::setIdentity() {

	m22 = 1;
	m02 = m03 = m12 = m13 = m20 = m21 = m23 = 0;
	m00 = 1;
	m01 = 0;
	m10 = 0;
	m11 = 1;
}