#include "GameLib\GameLib.h"
#include "Animation.h"
#include "AnimationNode.h"
#include "Element.h"
#include "Attribute.h"
using namespace GameLib;
Animation::Animation(const Element &e):
	_animationNodes(0),
	_nodesNumber(0)
{
	
	ASSERT(*e.getName() == "Animation");
	int an = e.getAttributeNumber();
	for (int i = 0; i < an; ++i) {
		const Attribute* a = e.getAttribute(i);
		if (*a->getName() == "name") {
			_name = *a->getValue();
		}
	}
	_nodesNumber = e.getChildNumber();
	_animationNodes = new AnimationNode*[_nodesNumber];
	for(int i = 0;  i < _nodesNumber; ++i) {
		const Element* c = e.getChild(i);
		if (*c->getName() == "Node") {
			cout << "addNode[" << i << "]"<<endl;
			_animationNodes[i] = new AnimationNode(*c);
		}
	}
	cout << "animatonTest" << endl;
	for (int i = 0; i < _nodesNumber; ++i) {
		ASSERT(0 <= i&&i < _nodesNumber);
		cout << "node[" << i << "]name:" << _animationNodes[i]->getName()->c_str();
	}
}
Animation::~Animation()
{
	for (int i = 0; i < _nodesNumber; ++i) {
		SAFE_DELETE(_animationNodes[i]);
	}
	SAFE_DELETE_ARRAY(_animationNodes);
}
const AnimationNode * Animation::getNode(const char* nodeName) const
{
	cout << "getAnimnode\n nodeNum:" << _nodesNumber << endl;
	cout << "nodeName:" << nodeName << endl;
	for (int i = 0; i < _nodesNumber; ++i) {
		cout << "index:" << i << endl;
		if (*_animationNodes[i]->getName() == nodeName) {
			return  _animationNodes[i];
		}
	}
	return 0;
}

int Animation::getNodesNumber() const
{
	return _nodesNumber;
}

const string * Animation::getName() const
{
	return &_name;
}
