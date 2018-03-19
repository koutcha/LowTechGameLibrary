#ifndef MATRIX23_H
#define MATRIX23_H
class Vector2D;
class Matrix23 {
private:
	double m00, m01, m02;
	double m10, m11, m12;
public:
	void multiply(Vector2D* out, const Vector2D in);

	void setTranslation(const Vector2D& v);
	void setRotation(double);
	void setScaling(const Vector2D& v);
	
	void translation(const Vector2D& v);
	void rotation(double);
	void scaling(const Vector2D& v);

	void operator *=(const  Matrix23& m);
};
#endif 
