#include "Model.h"
#include "Vector3D.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include"Batch.h"

Model::Model(const Batch* batch):
	position(0.0,0.0,0.0),
	angle(0.0,0.0,0.0),
	scale(1.0,1.0,1.0),
	color(1.0,1.0,1.0),
	batch(batch)
{

}

Model::~Model()
{
	batch = 0;
}
void Model::draw(
	const Matrix44& pvMatrix,
	const Vector3D& ligthVector,
	const Vector3D& lightColor,
	const Vector3D& ambient)const
{
	Matrix34 worldMatrix;
	worldMatrix.setTranslation(position);
	worldMatrix.rotateY(angle.y);
	worldMatrix.rotateX(angle.x);
	worldMatrix.rotateZ(angle.z);
	worldMatrix.scale(scale);
	
}
void Model::draw(const Matrix44 & projectionViewMatrix) const
{
	Matrix34 worldMatrix;
	worldMatrix.setTranslation(position);
	worldMatrix.rotateY(angle.y);
	worldMatrix.rotateX(angle.x);
	worldMatrix.rotateZ(angle.z);
	worldMatrix.scale(scale);
	Matrix44 pvwm;
	pvwm.setMul(projectionViewMatrix, worldMatrix);

}
Vector3D Model::getPosition() const
{
	return position;
}

void Model::setPosition(const Vector3D & position)
{
	this->position = position;
}

void Model::setAngle(const Vector3D & angle)
{
	this->angle = angle;
}

void Model::setScale(const Vector3D & scale)
{
	this->scale = scale;
}
