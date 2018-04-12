#include "Matrix23.h"
#include "Vector2D.h"
#include "GameLib\Math.h"
using namespace std;
using namespace GameLib;
void Matrix23::multiply(Vector2D * out, const Vector2D in)
{
	double tmp = in.x;
	out->x = m00*in.x + m01*in.y + m02;
	out->y = m10*tmp + m11*in.y + m12;
}
void Matrix23::setTranslation(const Vector2D & v)
{
	m00 = m11 = 1.0;
	m01 = m10 = 0.0;
	m02 = v.x;
	m12 = v.y;
}

void Matrix23::setRotation(double angle)
{
	double s = sin(angle);
	double c = cos(angle);
	m00 = m11 = c;
	m01 = -s;
	m10 = s;
	m02 = m12 = 0.0;
}

void Matrix23::setScaling(const Vector2D & v)
{
	m00 = v.x;
	m11 = v.y;
	m10 = m01 = m02 = m12 = 0;
}

void Matrix23::translation(const Vector2D & v)
{
	Matrix23 t;
	t.setTranslation(v);
	*this *= t;
}

void Matrix23::rotation(double angle)
{
	Matrix23 t;
	t.setRotation(angle);
	*this *= t;
}

void Matrix23::scaling(const Vector2D & v)
{
	Matrix23 t;
	t.setScaling(v);
	*this *= t;
}

void Matrix23::operator*=(const Matrix23 & m)
{
	double tx;
	double ty;
	tx = m00; ty = m01;
	m00 = tx*m.m00 + ty*m.m10;
	m01 = tx*m.m01 + ty*m.m11;
	m02 = tx*m.m02 + ty*m.m12 + m02;
	
	tx = m10; ty = m11;

	m10 = tx*m.m00 + ty*m.m10;
	m11 = tx*m.m01 + ty*m.m11;
	m12 = tx*m.m02 + ty*m.m12 + m12;

}
