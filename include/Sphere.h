#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3D.h"
class Batch;
class VertexBuffer;
class IndexBuffer;
class Matrix44;
class Matrix34;
class UVSphere {
private:
	Vector3D _position;
	Vector3D _angle;
	Vector3D _scale;
	Batch* _batch;
	VertexBuffer* _vertex;
	IndexBuffer* _index;

public:
	UVSphere(int n,double r);
	UVSphere(bool isInverted);
	~UVSphere();
	Batch* getBatch()const;
	void draw(
		const Matrix44& projectionViewMatrix,
		const Vector3D& lightVector,
		const Vector3D& lightColor,
		const Vector3D& ambient,
		const Vector3D& diffuseColor)const;
};
#endif
