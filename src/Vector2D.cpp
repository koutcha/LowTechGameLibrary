#include "Vector2D.h"

Vector2D::Vector2D()
{
}

Vector2D::Vector2D(int aX, int aY)
{
	this->x = static_cast<double>(aX);
	this->y = static_cast<double>(aY);
}

Vector2D::Vector2D(double aX, double aY):x(aX),y(aY)
{
}



Vector2D& Vector2D::operator+=(const Vector2D & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D & v)
{ 
	x -= v.x;
	y -= v.y;
	return *this;
}

Vector2D& Vector2D::operator=(const Vector2D & v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector2D& Vector2D::operator*=(double s)
{
	x *= s;
	y *= s;
	return*this;
}

void Vector2D::setSub(const Vector2D &v1, const Vector2D &v2)
{
	*this = v1;
	*this -= v2;
}

void Vector2D::setAdd(const Vector2D &v1, const Vector2D &v2)
{
	*this = v1;
	*this += v2;
}

double Vector2D::cross(const Vector2D & v)const
{
	return x * v.y - y * v.x;
}
