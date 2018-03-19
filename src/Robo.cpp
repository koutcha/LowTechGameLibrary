#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "Library\Robo.h"
#include "Library\Matrix34.h"
#include "Library\Matrix44.h"
#include "Library\Vector3D.h"
#include "Library\Cube.h"
#include "GameLib\Framework.h"
#include "GameLib\GameLib.h"
#include "GameLib\Math.h"
#include "Library\JoyPad.h"
#include <sstream>
#include "Library\Model.h"
#include "Library\GraphicsDatabase.h"
using namespace GameLib;
using namespace std;
Robo::Robo(int id,Model* model):
	_id(id),
	_model(model),
	_angleY(0),
	_position(0,0,0)
{

}
Robo::Robo(int id,GraphicsDatabase& gd) :
	_id(id),
	_model(0),
	_angleY(0),
	_position(0, 0, 0)
{
	_model = gd.createModel("robo.txt");
}

Robo::Robo():
	_id(0),
	_model(0),
	_angleY(0),
	_position(0, 0, 0)
{
}



Robo::~Robo()
{
	Framework f = Framework::instance();
	SAFE_DELETE(_model);

}

void Robo::draw(const Matrix44& pvm)
{
	
	_model->draw(pvm);
}

void Robo::draw(const Matrix44 & pvm, const Vector3D & lightVector, const Vector3D & lightColor, Vector3D & ambient) const
{
	_model->draw(pvm,lightVector,lightColor,ambient);
}

void Robo::update(const Vector3D& enemyPos,const Vector3D& viewVector)
{

	JoyPad* j = JoyPad::getInstance();
	Vector3D targetVector = viewVector;
	double subAbs = GameLib::sqrt(targetVector.x*targetVector.x + targetVector.y*targetVector.y + targetVector.z*targetVector.z);
	targetVector.x /= subAbs;
	targetVector.y /= subAbs;
	targetVector.z /= subAbs;

	ostringstream oss;
	oss << targetVector.x << ";" << targetVector.y << ";" << targetVector.z;
	Framework f = Framework::instance();
	f.drawDebugString(10, 1, oss.str().c_str());

	double sp = 0.5;
	targetVector.x *= sp;
	targetVector.y = 0;
	targetVector.z *= sp;



	Vector3D nextPosition = _position;
	if (j->getYAxsis(0) < 22767) {
		nextPosition += targetVector;
	}
	else if (j->getYAxsis(0) > 42767) {
		nextPosition -= targetVector;
	}
	Matrix34 subM;
	subM.setRotationY(90);
	subM.multiply(&targetVector, targetVector);

	if (j->getXAxsis(0) < 22767) {
		nextPosition += targetVector;
	}
	else if (j->getXAxsis(0) > 42767) {
		nextPosition -= targetVector;
	}
	if (j->isOn(JoyPad::Button1,0) ){
		Vector3D toEnemy;
		toEnemy.setSub(enemyPos, nextPosition);
		double angle = GameLib::atan2(toEnemy.x, toEnemy.z);
		nextPosition.y += 0.5;
		setAngleY(angle);
	}
	else {
		if (nextPosition.y > 0) {
			nextPosition.y -= 0.5;
		}
	}
	setPosition(nextPosition);
}

const Vector3D  Robo::getPosition() const
{
	return _position;
}

double Robo::getAngleY() const
{
	return _angleY;
}

void Robo::setPosition(const Vector3D & position)
{
	_position = position;
	_model->setPosition(_position);
}

void Robo::setAngleY(double angle)
{
	double sub = angle - _angleY;
	_angleY = angle;
	_model->setAngle(Vector3D(0.0,_angleY,0.0));
}
