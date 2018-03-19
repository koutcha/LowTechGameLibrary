#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
using namespace std;
class Element;
class AnimationNode;
class Animation {
private:
	AnimationNode** _animationNodes;
	int _nodesNumber;
	string _name;
public:
	Animation(const Element& e);
	~Animation();
	const AnimationNode * getNode(const char * nodeName) const;
	int getNodesNumber()const;
	const string* getName()const;

};
#endif