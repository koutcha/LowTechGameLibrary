#include "PointLight.h"



PointLight::PointLight()
{
}


PointLight::~PointLight()
{
}

void PointLight::setColor(Vector3D& color)
{
	_color = color;
}

void PointLight::setPosition(Vector3D& position)
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
