#ifndef ANIMATIONNODE_H
#define ANIMATIONNODE_H
#include <string>
using namespace std;
class Vector3D;
class Element;
class Curve;
class AnimationNode {
private:
	Curve** _curves;
	int _curveNumber;
	string _name;
public:
	AnimationNode(const Element& e);
	AnimationNode();
	~AnimationNode();
	void getData(Vector3D * position, Vector3D * angle, Vector3D * scale, Vector3D * qAxis, double * qValue, bool * useQuartanion, double time) const;
	//void getData(Vector3D*, Vector3D*, Vector3D*, double)const;
	const string* getName()const;
};
#endif