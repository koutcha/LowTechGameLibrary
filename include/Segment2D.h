#ifndef PRIMITIVE_L2D
#define PRIMITIVE_L2D
#include "Vector2D.h"
class Segment2D
{
public:
	Segment2D();
	~Segment2D();
	void setPoint(const Vector2D& sp,const Vector2D&vector);
	void pararellMove(const Vector2D&);

	Vector2D getEndPoint()const;
	Vector2D sp;
	Vector2D vector;
	bool collisionSegment(const Segment2D& segment)const;
	bool collisionSegment(const Segment2D & segment, Vector2D * outPositon) const;
};
#endif