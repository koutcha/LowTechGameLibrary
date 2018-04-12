#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "Vector3D.h"
class Matrix44;
class PointLight
{
public:
	PointLight();
	~PointLight();
	void setColor(const Vector3D&);
	void setPosition(const Vector3D&);
	Vector3D getColor()const;
	Vector3D getPosition()const;
	//�ꏊ�m�F�p

	void drawLight(const Matrix44& pvm, double size)const;
private:
	//�F
	Vector3D _color;
	Vector3D _position;

	//���������̉�
	bool attenuation;

};
#endif