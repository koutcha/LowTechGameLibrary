#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "Vector3D.h"
class PointLight
{
public:
	PointLight();
	~PointLight();
	void setColor(Vector3D&);
	void setPosition(Vector3D&);
	Vector3D getColor()const;
	Vector3D getPosition()const;
private:
	//色（色情報だけではなく光強度も含む
	Vector3D _color;
	Vector3D _position;
	
	//距離減数の可否
	bool attenuation;

};
#endif