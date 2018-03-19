#ifndef ROBO_H
#define ROBO_H
#include "Vector3D.h"
class Matrix34;
class Matrix44;
class Model;
class GraphicsDatabase;
namespace GameLib {
	class Texture;
}
class Robo {
private:
	int _id;
	Model* _model;
	double _angleY;
	Vector3D _position;
public:
	Robo();
	Robo(int id,Model* model);
	Robo(int id, GraphicsDatabase & gd);
	~Robo();
	void draw(const Matrix44& pvm);
	void draw(const Matrix44& pvm, const Vector3D& lightVector, const Vector3D& lightColor, Vector3D& ambient)const;
	void update(const Vector3D & enemyPos, const Vector3D & viewVector);
	const  Vector3D getPosition() const;
	double getAngleY() const;
	void setPosition(const Vector3D&);
	void setAngleY(double);

};
#endif