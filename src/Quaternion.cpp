#include "Quaternion.h"
#include "GameLib\Math.h"
#include <math.h>
using namespace GameLib;
Quaternion::Quaternion()
{
}

void Quaternion::mulitiply(Vector3D * out, const Vector3D & in) const
{

	Quaternion qx;
	Quaternion x;
	x.setVector(in);
	qx.setMul(*this, x);
	Quaternion cq;
	cq.setConjugate(*this);
	qx *= cq;
	out->x = qx.v.x;
	out->y = qx.v.y;
	out->z = qx.v.z;

}
void Quaternion::getEuler(Vector3D * out) const
{
	double x = v.x;
	double y = v.y;
	double z = v.z;

	
}
void Quaternion::setConjugate(const Quaternion& q) {
	w = q.w;
	v = q.v;
	v *= -1.0;
}
void Quaternion::setRotation(const Vector3D & axis, double angle)
{
	
	v = axis;
	v.normalize();
	
	v.x *= GameLib:: sin(angle/2.0);
	v.y *= GameLib::sin(angle / 2.0);
	v.z *= GameLib::sin(angle / 2.0);
	w = GameLib::cos(angle/2);
}

void Quaternion::setVector(const Vector3D& vector)
{
	w = 0;
	v = vector;
}

void Quaternion::operator*=(const Quaternion & q)
{
	Vector3D cross,wd_v,w_vd;
	wd_v = v;
	w_vd = q.v;
	wd_v *= q.w;
	w_vd *= w;
	cross.setCross(v, q.v);
	w = w*q.w - v.dot(q.v);
	v = w_vd;
	v += wd_v;
	v += cross;
}
void Quaternion::setMul(const Quaternion& q1, const Quaternion q2) {
	v = q1.v;
	w = q1.w;

	*this *= q2;
}
