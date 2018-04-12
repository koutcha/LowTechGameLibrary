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
	//場所確認用

	void drawLight(const Matrix44& pvm, double size)const;
private:
	//色
	Vector3D _color;
	Vector3D _position;

	//距離減数の可否
	bool attenuation;

};
#endif