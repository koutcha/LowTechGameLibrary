#include "Vector3D.h"
#include "GameLib\Math.h"
using namespace GameLib;
Vector3D::Vector3D()
{
}

Vector3D::Vector3D(int aX, int aY,int aZ)
{
	this->x = static_cast<double>(aX);
	this->y = static_cast<double>(aY);
	this->z = static_cast<double>(aZ);
}

Vector3D::Vector3D(double aX, double aY,double aZ) :x(aX), y(aY),z(aZ)
{
}

void Vector3D::set(double aX,double aY,double aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

void Vector3D::setAdd(const Vector3D & v1, const Vector3D & v2)
{
	x = v1.x + v2.x;
	y = v1.y + v2.y;
	z = v1.z + v2.z;

}

void Vector3D::setSub(const Vector3D & v1, const Vector3D & v2)
{
	x = v1.x - v2.x;
	y = v1.y - v2.y;
	z = v1.z - v2.z;

}

void Vector3D::setMul(double scalar, const Vector3D & v)
{
	x = scalar*v.x;
	y = scalar*v.y;
	z = scalar*v.z;
}

void Vector3D::setCross(const Vector3D& v1, const Vector3D& v2) {

	x = v1.y*v2.z - v2.y*v1.z;
	y = v1.z*v2.x - v2.z*v1.x;
	z = v1.x*v2.y - v2.x*v1.y;
}
double Vector3D::dot(const Vector3D & v)const
{
	return x*v.x + y*v.y + z*v.z;
}
void Vector3D::normalize() {
	double d = sqrt(x*x + y*y + z*z);

	x /= d;
	y /= d;
	z /= d;
}
double Vector3D::length() {
	return sqrt(x*x + y*y + z*z);
}
void Vector3D::operator+=(const Vector3D & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vector3D::operator-=(const Vector3D & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void Vector3D::operator=(const Vector3D & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}
void Vector3D::operator*=(double s) {
	x *= s;
	y *= s;
	z *= s;
}