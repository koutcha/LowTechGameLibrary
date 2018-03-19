#ifndef VECTOR3D_H
#define VECTOR3D_H
class Vector3D {
public:
	Vector3D();
	Vector3D(int x, int y,int z);
	Vector3D(double x, double y,double z);

	void set(double,double,double);
	void setAdd(const Vector3D& v1, const Vector3D& v2);
	void setSub(const Vector3D& v1, const Vector3D& v2);
	void setMul(double scalar ,const Vector3D& v);
	void setCross(const Vector3D & v1, const Vector3D & v2);
	double dot(const Vector3D& v) const;
	void normalize();

	double length();

	void operator+=(const Vector3D& v);
	void operator -=(const Vector3D& v);
	void operator = (const Vector3D& v);

	void operator*=(double s);

	double x;
	double y;
	double z;

};
#endif
