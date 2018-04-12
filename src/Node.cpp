#include "Node.h"
#include "Matrix34.h"
#include "Matrix44.h"
//#include "Batch.h"
#include "AnimationNode.h"
#include "Quaternion.h"
#include "GameLib\GameLib.h"

using namespace GameLib;
//#include<string>
//using namespace std;
Node::Node() :
	_children(0),
	_batch(0),
	_childrenNumber(0),
	_position(0, 0, 0),
	_angle(0, 0, 0),
	_rotationAxis(0,0,0),
	_qAngle(0.0),
	_useQuaternion(false),
	_scale(1.0, 1.0, 1.0),
	_color(1.0,1.0,1.0),
	_specular(5.0,5.0,5.0),
	_specularPow(50),
	_shader(Batch::GOURAND_SHADING)
{

}

Node::Node(const Batch * batch, int chilerenNumber):
	_children(0),
	_batch(batch),
	_childrenNumber(chilerenNumber),
	_position(0,0,0),
	_angle(0,0,0),
	_rotationAxis(0, 0, 0),
	_qAngle(0.0),
	_useQuaternion(false),
	_scale(1.0,1.0,1.0),
	_color(1.0, 1.0, 1.0),
	_specular(1.0, 1.0, 1.0),
	_specularPow(50),
	_shader(Batch::GOURAND_SHADING)
{
	if (chilerenNumber != 0) {
		_children = new Node*[chilerenNumber];
	}
	else {
		_children = nullptr;
	}
	
}

Node::~Node()
{
	if (_children != nullptr) 
	{
		SAFE_DELETE_ARRAY(_children);
	}
	
	_batch = nullptr;

}


void Node::draw(const Matrix44 & projectionMatrix, const Matrix34 & parentWorldMatrix, const Vector3D & lightVector, const Vector3D & lightColor, const Vector3D & ambient,const Vector3D& eyePosition)const
{
	Matrix34 wm;
	wm.setIdentity();
	Quaternion q;
	wm.setTranslation(_position);
	if (_useQuaternion) {
		q.setRotation(_rotationAxis, _qAngle);
		wm.rotateByQuaternion(q);
	}
	else {
		wm.rotateY(_angle.y);
		wm.rotateX(_angle.x);
		wm.rotateZ(_angle.z);
	}
	wm.scale(_scale);
	wm.setMul(parentWorldMatrix, wm);

	if (_batch) {
		_batch->draw(projectionMatrix, wm, lightVector, lightColor, ambient, _color,_specular,_specularPow,eyePosition,_shader);
	}
	for (unsigned i = 0; i < _childrenNumber; i++) {
		_children[i]->draw(projectionMatrix, wm, lightVector, lightColor, ambient,eyePosition);
	}
}

void Node::draw(const Matrix44 & projectionViewMatrix, const Matrix34 & worldMatrix, const PointLight * lightSources, int lightNumber, const Vector3D & ambient, const Vector3D & eyeVector) const
{
	Matrix34 wm;
	wm.setIdentity();
	Quaternion q;
	wm.setTranslation(_position);
	if (_useQuaternion) {
		q.setRotation(_rotationAxis, _qAngle);
		wm.rotateByQuaternion(q);
	}
	else {
		wm.rotateY(_angle.y);
		wm.rotateX(_angle.x);
		wm.rotateZ(_angle.z);
	}
	wm.scale(_scale);
	wm.setMul(worldMatrix, wm);

	if (_batch) {
		_batch->draw(projectionViewMatrix, wm, lightSources, lightNumber, ambient, _color, _specular, _specularPow, eyeVector, _shader);
	}
	for (unsigned i = 0; i < _childrenNumber; i++) {
		_children[i]->draw(projectionViewMatrix, wm, lightSources, lightNumber, ambient, eyeVector);
	}
}


void Node::setTranslation(const Vector3D& v)
{
	_position = v;
}

void Node::setRotation(const Vector3D& v)
{
	_angle = v;
	_useQuaternion = false;
}

void Node::setQuaternionRotation(const Vector3D & axis, double angle)
{
	_qAngle = angle;
	_rotationAxis = axis;
	_useQuaternion = true;
}

void Node::setScale(const Vector3D& v)
{
	_scale = v;
}

void Node::setBatch(const Batch &batch)
{
	_batch = &batch;
}

void Node::setColor(const Vector3D &color)
{
	_color = color;
}

void Node::setSpecular(const Vector3D &specular,double specularPow)
{
	_specular = specular;
	_specularPow = specularPow;
}

void Node::setShader(Batch::ShadingMode shader)
{
	_shader = shader;
}

void Node::setName(const char * name)
{
	_name = name;
}

void Node::setChild(int index, Node *node)
{
	ASSERT(0 <= index && index < _childrenNumber);
	_children[index] = node;
}

void Node::setChildNumber(int childNum)
{
	_childrenNumber = childNum;
	_children = new Node*[childNum];
}

void Node::update(double time, const AnimationNode& animationNode)
{
	animationNode.getData(&_position, &_angle, &_scale,&_rotationAxis,&_qAngle,&_useQuaternion,time);
}

const Batch * Node::getBatch() const
{
	return _batch;
}

const Vector3D * Node::getTranslation() const
{
	return &_position;
}

const Vector3D * Node::getRotation() const
{
	return &_angle;
}

const Vector3D * Node::getScale() const
{
	
	return &_scale;
}

const string * Node::getName() const
{
	return &_name;
}
Batch::ShadingMode Node::getShader() const
{
	return _shader;
}
void Node::writeChildrenConsole()const {
	cout << _name.c_str() << " children" << endl;
	for (unsigned i = 0; i < _childrenNumber; ++i) {
		cout << i << ": " << _children[i]->getName()->c_str() << endl;
	}
}