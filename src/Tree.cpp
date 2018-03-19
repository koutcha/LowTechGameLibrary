#include "Tree.h"
#include "Node.h"
#include "Matrix34.h"
#include "Quaternion.h"
#include "Animation.h"
#include "AnimationNode.h"
#include "TreeTemplate.h"
#include "NodeTemplate.h"
#include "Batch.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
Tree::Tree(const TreeTemplate & treeTemplate):
	_position(0,0,0),
	_angle(0,0,0),
	_scale(1.0,1.0,1.0),
	_rotationAxis(0, 0, 0),
	_qAngle(0.0),
	_useQuaternion(false),
	_nodes(0),
	_nodeNumber(0),
	_time(0)
{
	_nodeNumber = treeTemplate.getNodeNumber();

	_nodes = new Node[_nodeNumber];
	

	for (int i = 0; i < _nodeNumber; ++i) {

		const NodeTemplate* nodeT = treeTemplate.getNode(i);
		cout << nodeT->getName()->c_str() << endl;
		_nodes[i].setName(nodeT->getName()->c_str());
		_nodes[i].setRotation(*nodeT->getRotation());
		_nodes[i].setTranslation(*nodeT->getTranslation());
		_nodes[i].setScale(*nodeT->getScale());
		_nodes[i].setBatch(*nodeT->getBatch());
		int childIndex = nodeT->getChild();
		int count = 0;
		if ( childIndex!= -1) {
			count++;
			while (treeTemplate.getNode(childIndex)->getBrother() != -1) {
				childIndex = treeTemplate.getNode(childIndex)->getBrother();
				count++;
			}
			_nodes[i].setChildNumber(count);
			childIndex = nodeT->getChild();
			for (int j = 0; j <count; ++j) {
				_nodes[i].setChild(j, &_nodes[childIndex]);
				childIndex = treeTemplate.getNode(childIndex)->getBrother();
			}
		}

	}
	for (int i = 0; i < _nodeNumber; ++i) {
		cout << "checkNode" << endl;
		cout << _nodes[i].getName()->c_str() << endl;
		if (_nodes[i].getBatch()) {
			cout << _nodes[i].getBatch()->getName()->c_str() << endl;
		}
		_nodes[i].writeChildrenConsole();
	}
	
}

Tree::~Tree()
{
	SAFE_DELETE_ARRAY(_nodes);

}


void Tree::draw(const Matrix44 & projectionViewMatrix, const Vector3D & lightVector, const Vector3D & lightColor, const Vector3D & ambient, const Vector3D & eyeVector) const
{
	Matrix34 wm;
	wm.setIdentity();
	wm.translate(_position);
	wm.rotateY(_angle.y);
	wm.rotateX(_angle.x);
	wm.rotateZ(_angle.z);
	wm.scale(_scale);
	_nodes->draw(projectionViewMatrix, wm, lightVector, lightColor, ambient,eyeVector);
}

void Tree::setPosition(const Vector3D &v)
{
	_position = v;
}

void Tree::setAngle(const Vector3D &v)
{
	_angle = v;
}

void Tree::setQuaternionRotation(const Vector3D & axis, double angle)
{
	_qAngle = angle;
	_rotationAxis = axis;
	_useQuaternion = true;
}

void Tree::setScale(const Vector3D &v)
{
	_scale = v;
}

Node * Tree::getNode(const char * name)
{
	for (int i = 0; i < _nodeNumber; i++) {
		if (*_nodes[i].getName() == name) {
			return &_nodes[i];
		}
	}
	return 0;
}

const Node * Tree::getNode(const char * name) const
{
	for (int i = 0; i < _nodeNumber; i++) {
		if (*_nodes[i].getName() == name) {
			return &_nodes[i];
		}
	}
	return 0;
}

void Tree::setAnimation(const Animation * animation)
{
	cout << "setAnimation" << endl;
	cout << "animationSize  :" << animation->getNodesNumber() << endl;

	cout << "treeSize          :" << this->_nodeNumber << endl;
	
	for (int i = 0; i < _nodeNumber; ++i) {
		cout << "node[" << i << "]" << endl;
		const AnimationNode* node = animation->getNode(_nodes[i].getName()->c_str());
		//cout << "set " << _nodes[i].getName()->c_str() << ":" << node->getName()->c_str() << endl;
		if (node) {
			_animationNodes[*node->getName()] = node;
			cout << "setAniNode;" << i << endl;
		}
	}
	_time += 0;
}

void Tree::update()
{
	for (int i = 0; i <_nodeNumber; ++i) {
		const string* nodeName = _nodes[i].getName();
		const AnimationNode* aniNode = _animationNodes[*nodeName];
		if (aniNode) {
			_nodes[i].update(_time, *_animationNodes[*nodeName]);
		}
		
	}
	_time+=1.0;

}
