#include "Segment2D.h"
#include"Vector2D.h"
Segment2D::Segment2D()
{
}

Segment2D::~Segment2D()
{
}

void Segment2D::setPoint(const Vector2D &sp,const  Vector2D &vector)
{
	this->sp = sp;
	this->vector = vector;
}

void Segment2D::pararellMove(const Vector2D &v)
{
	sp += v;
}

Vector2D Segment2D::getEndPoint()const
{
	Vector2D ep;
	ep = sp;
	ep += vector;
	return ep;
}

bool Segment2D::collisionSegment(const Segment2D & segment) const
{

	Vector2D v;
	v.setSub(segment.sp,sp);
	double crossV1V2 = vector.cross(segment.vector);
	if (crossV1V2 == 0) {
		return false;
	}
	double crossVV1 = v.cross(vector);
	double crossVV2 = v.cross(segment.vector);

	double t1 = crossVV2 / crossV1V2;
	double t2 = crossVV1 / crossV1V2;
	const double epsilon = 0.0000000001;
	
	return  !(t1 + epsilon < 0 || t1 - epsilon>1.0 || t2 + epsilon < 0 || t2 - epsilon>1.0);
	
}
bool Segment2D::collisionSegment(const Segment2D & segment,Vector2D* outPosition) const
{
	Vector2D v;
	v.setSub(segment.sp, sp);
	double crossV1V2 = vector.cross(segment.vector);
	if (crossV1V2 == 0) {
		return false;
	}
	double crossVV1 = v.cross(vector);
	double crossVV2 = v.cross(segment.vector);

	double t1 = crossVV2 / crossV1V2;
	double t2 = crossVV1 / crossV1V2;
	const double epsilon = 0.000000000001;
	if (t1 + epsilon < 0 || t1 - epsilon>1.0 || t2 + epsilon < 0 || t2 - epsilon>1.0) {
		return false;
	}
	*outPosition = vector;
	*outPosition *= t1;
	*outPosition += sp;

	return true;
}


