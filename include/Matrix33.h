#ifndef MATRIX33_H
#define MATRIX33_H
class Matrix34;
class Vector3D;
class Matrix33 {
private:
	friend class Matrix34;
	double m00, m01, m02;
	double m10, m11, m12;
	double m20, m21, m22;
public:
	void setReduction(const Matrix34& m);
	void setReductionInverse(const Matrix34& m);
	void setReductionTransInverse(const Matrix34& m);
	void multiply(Vector3D* out, const Vector3D& in)const;
};
#endif