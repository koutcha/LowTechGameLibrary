#ifndef VECTOR2D_H
#define VECTOR2D_H
class Vector2D {
public:
	Vector2D();
	Vector2D(int x, int y);
	Vector2D(double x, double y);
	
	void operator+=(const Vector2D& v);
	void operator -=(const Vector2D& v);
	void operator = (const Vector2D& v);
	void operator*=(double s);
	void setSub(const Vector2D&, const Vector2D&);
	void setAdd(const Vector2D&, const Vector2D&);

	double cross(const Vector2D& v)const;

	double x;
	double y;

};
#endif
