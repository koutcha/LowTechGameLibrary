#include "Camera.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include"GameLib\Framework.h"
using namespace GameLib;
Camera::Camera():
	position(0,0,1),
	target(0,0,0),
	fieldOfViewY(60.0),
	nearClip(1.0),
	farClip(10000.0)
{
}

Camera::~Camera()
{
}

void Camera::setPosition(const Vector3D& position)
{
	this->position = position;
}

void Camera::setTarget(const Vector3D& targetPosition)
{
	target = targetPosition;
}

void Camera::setFieldOfView(double fieldOfViewY)
{
	this->fieldOfViewY = fieldOfViewY;
}

void Camera::setNearClip(double nearClip)
{
	this->nearClip = nearClip;
}

void Camera::setFarClip(double farClip)
{
	this->farClip = farClip;
}

const Vector3D  Camera::getPosition() const
{
	return position;
}

const Vector3D  Camera::getTarget() const
{
	return target;
}

double Camera::getFieldOfView() const
{
	return fieldOfViewY;
}

double Camera::getNearClip() const
{
	return nearClip;
}

double Camera::getFarClip() const
{
	return farClip;
}

void Camera::createProjectionViewMatrix(Matrix44 *out) const
{

	Matrix34 viewMatrix;
	viewMatrix.setViewTransform(position, target);
	Framework f = Framework::instance();
	out->setPerspectiveTransform(fieldOfViewY,
		static_cast<double>(f.width()),
		static_cast<double>(f.height()), 
		nearClip,
		farClip);
	*out *= viewMatrix;	
}
