//#include "GameLib\Framework.h"
//using namespace GameLib;
#ifndef RECTANGLE_H
#define RECTANGLE_H
class Vector3D;
class Matrix44;
namespace {
	class Texture;
}
class Rectangle {
private:
	Vector3D* vertexes;

	double width;
	double depth;

	double x;
	double y;
	double z;
public:
	Rectangle(double x,double y, double z, double width, double depth);
	~Rectangle();
	void setPoint(double x, double y, double z);
	void draw(const Matrix44& pvwm)const;
	void draw(const Matrix44& pvwm, const double uv[][2], const GameLib::Texture* texture)const;
	
};
#endif