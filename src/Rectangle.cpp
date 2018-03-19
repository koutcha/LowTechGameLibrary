#include "GameLib\Framework.h"
using namespace GameLib;
#include "Library\Rectangle.h"
#include "Library\Vector3D.h"
#include "Library\Matrix34.h"
#include "Library\Matrix44.h"

Rectangle::Rectangle(double x, double y, double z, double width, double depth):
	x(x),
	y(y),
	z(z),
	width(width),
	depth(depth)
{
	this->vertexes = new  Vector3D[4];
	double subX = x - width / 2;
	double subZ = z - depth / 2;
	double xw = width + subX;
	double zd = depth + subZ;
	vertexes[0] = Vector3D(subX,y, subZ);
	vertexes[1] = Vector3D(xw,y, subZ);
	vertexes[2] = Vector3D(subX, y, zd);
	vertexes[3] =  Vector3D(xw, y, zd);

}

Rectangle::~Rectangle()
{
	SAFE_DELETE(vertexes);
}

void Rectangle::setPoint(double aX, double aY, double aZ)
{
	double subX = aX - x;
	double subY = aY - y;
	double subZ = aZ - z;

	Matrix34 m;
	m.setTranslation(Vector3D(subX, subY, subZ));
	x = aX;
	y = aY;
	z = aZ;
	for (int i = 0; i < 4; i++) {
		m.multiply(&vertexes[i], vertexes[i]);
	}

}

void Rectangle::draw(const Matrix44 & pvwm)const
{
	Framework f = Framework::Framework();
	double p4[4][4];
	//Žè“®‚Åz *= w‚ð‚·‚é‚È‚ç‚â‚é
	for (int i = 0; i < 4; i++) {
		pvwm.multiply(p4[i], vertexes[i]);
	}
	unsigned c[4];
	c[0] = 0xffff0000; //Ô
	c[1] = 0xff00ff00; //—Î
	c[2] = 0xff0000ff; //Â
	c[3] = 0xffffffff; //”’

	
	f.drawTriangle3DH(p4[0], p4[1], p4[2], 0, 0, 0, c[0], c[1], c[2]);
	f.drawTriangle3DH(p4[0], p4[3], p4[2], 0, 0, 0, c[0], c[3], c[2]);
}

void Rectangle::draw(const Matrix44 & pvwm, const double  uv[][2], const GameLib::Texture* texture) const
{
	Framework f = Framework::Framework();
	f.setTexture(texture);
	double p4[4][4];

	for (int i = 0; i < 4; i++) {
	pvwm.multiply(p4[i], vertexes[i]);
	}
	f.drawTriangle3DH(p4[0], p4[1], p4[2], uv[0],uv[1],uv[2]);
	f.drawTriangle3DH(p4[3], p4[1], p4[2], uv[3], uv[1], uv[2]);


}	





