#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vector3D.h"
class Quaternion{
private:
	friend class Matrix34;
	Vector3D v;
	double w;
public:
	Quaternion();
	void mulitiply(Vector3D* out, const Vector3D& in)const;
	void getEuler(Vector3D* out)const;
	void setConjugate(const Quaternion & q);
	void setRotation(const Vector3D& axis, double angle);
	void setVector(const Vector3D&);
	void operator *=(const Quaternion& q);
	void setMul(const Quaternion & q1, const Quaternion q2);
};
#endif