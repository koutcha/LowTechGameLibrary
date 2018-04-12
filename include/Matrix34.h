#ifndef MATRIX34_H
#define MATRIX34_H
class Vector3D;
class Quaternion;
class Matrix34 {
private:
	friend class Matrix33;
	friend class Matrix44;
	friend class Batch;
	double m00, m01, m02, m03;
	double m10, m11, m12, m13;
	double m20, m21, m22, m23;
public:
	Matrix34() {};
	void multiply(Vector3D* out, const Vector3D& in)const;
	void setTranslation(const Vector3D& v);
	void setRotationX(double);
	void setRotationY(double);
	void setRotationZ(double);
	void setScaling(const Vector3D& v);

	void setViewTransform(const Vector3D& p,const Vector3D& t);

	void setQuaternionRotaion(const Quaternion & q);
	void rotateByQuaternion(const Quaternion & q);
	void translate(const Vector3D& v);
	void rotateX(double);
	void rotateY(double);
	void rotateZ(double);
	void scale(const Vector3D& v);



	Matrix34& operator *=(const Matrix34& m);

	void setMul(const Matrix34 & m1, const Matrix34 & m2);

	void setIdentity();

};
#endif
