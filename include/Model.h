#ifndef MODEL_H
#define MODEL_H
#include "Vector3D.h"
class Batch;
class Matrix44;
class Model {
private:
	Vector3D position;
	Vector3D angle;
	Vector3D scale;
	Vector3D color;
	const Batch* batch;
public:
	Model(const Batch*);
	~Model();
	void draw(const Matrix44 & pvMatrix, const Vector3D & ligthVector, const Vector3D & lightColor, const Vector3D & ambient)const;
	void draw(const Matrix44& projectionViewMatrix)const;
	Vector3D getPosition()const;
	void setPosition(const Vector3D&);
	void setAngle(const Vector3D&);
	void setScale(const Vector3D&);

};
#endif
