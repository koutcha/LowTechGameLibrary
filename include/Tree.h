#ifndef ANIMATION_TREE_H
#define ANIMATION_TREE_H
#include "Vector3D.h"
#include <map>
#include <string>
class Node;
class TreeTemplate;
class Matrix44;
class Animation;
class AnimationNode;
using namespace std;
class Tree {
public:
	Tree(const TreeTemplate&);
	~Tree();
	void draw(
		const Matrix44& projectionViewMatrix,
		const Vector3D& lightVector,
		const Vector3D& lightColor,
		const Vector3D& ambient,
		const Vector3D& eyeVector)const;
	void setPosition(const Vector3D&);
	void setAngle(const Vector3D&);
	void setQuaternionRotation(const Vector3D& axis, double angle);
	void setScale(const Vector3D&);
	Node* getNode(const char* name);
	const Node* getNode(const char* name) const;
	void setAnimation(const Animation*);
	void update();
private:
	Vector3D _position;
	Vector3D  _angle;
	Vector3D _scale;

	bool _useQuaternion;
	Vector3D _rotationAxis;
	double _qAngle;
	Node * _nodes;
	//animatinNode‚Ídatabase‚Ådel
	map<string,const AnimationNode*> _animationNodes;
	int _nodeNumber;
	double _time;
};
#endif