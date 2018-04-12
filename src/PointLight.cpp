#include "PointLight.h"
#include "GameLib\Framework.h"
#include "Matrix34.h"
#include "Matrix44.h"
using namespace GameLib;
PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::setColor(const Vector3D& color)
{
	_color = color;
}

void PointLight::setPosition(const Vector3D& position)
{
	_position = position;
}

Vector3D PointLight::getColor() const
{
	return _color;
}

Vector3D PointLight::getPosition() const
{
	return _position;
}

void PointLight::drawLight(const Matrix44 & pvm, double size) const
{
	Framework f = Framework::instance();
	f.setBlendMode(Framework::BLEND_OPAQUE);
	Vector3D p[4];
	p[0] = Vector3D(0.0, 0.0, 0.5);
	p[1] = Vector3D(0.0, 0.5, 0.0);
	p[2] = Vector3D(0.43, -0.25, 0.0);
	p[3] = Vector3D(-0.43, -0.25, 0.0);
	Matrix34 translate;
	translate.setTranslation(_position);
	Matrix44 pvwm;
	pvwm.setMul(pvm, translate);
	
}
