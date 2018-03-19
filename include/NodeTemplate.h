#ifndef ANIMATION_NODETEMPLATE_H
#define ANIMATION_NODETEMPLATE_H
#include "Vector3D.h"
#include<string>
using namespace std;
class Batch;
class NodeTemplate {
private:
	friend class TreeTemplate;
	int _oldestChild;
	int _youngerBrother;
	const Batch* _batch;
	unsigned _childrenNumber;
	Vector3D _transration;
	Vector3D _rotation;
	Vector3D _scale;
	string _name;
public:
	NodeTemplate();
	~NodeTemplate();
	int getChild() const;
	int getBrother() const;
	const Batch* getBatch() const;
	const Vector3D* getTranslation() const;
	const Vector3D* getRotation() const;
	const Vector3D* getScale() const;
	const string* getName() const;
};
#endif