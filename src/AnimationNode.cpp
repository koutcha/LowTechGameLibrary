#include "AnimationNode.h"
#include "Element.h"
#include "Attribute.h"
#include "Curve.h"
#include "QCurve.h"
#include "Vector3D.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
AnimationNode::AnimationNode(const Element& e)
	:_curves(0),
	_curveNumber(0)
{
	for (int i = 0; i < e.getAttributeNumber(); ++i) {
		const Attribute* a = e.getAttribute(i);
		cout << "add:" << a->getName()->c_str() << endl;
		if (*a->getName() == "name") {
			_name = *a->getValue();
		}
	}
	int cn = e.getChildNumber();
	cout << "cn:" << cn << endl;
	_curveNumber = cn;
	_curves = new Curve*[cn];
	for (int i = 0; i < cn; ++i) {
		const Element* ce = e.getChild(i);

		if (*ce->getName() == "Curve") {
			_curves[i] = new Curve(*ce);
		}
		else if (*ce->getName() == "QCurve") {
			_curves[i] = new QCurve(*ce);
		}
	}
}

AnimationNode::AnimationNode()
	:_curves(0),
	_curveNumber(0)
{

}

AnimationNode::~AnimationNode()
{
	for (int i = 0; i < _curveNumber; ++i) {
		//ŽÀ‘Ì‚Ì”jšÊ
		SAFE_DELETE(_curves[i]);
	}
	//ƒ|ƒCƒ“ƒ^”z—ñ‚Ì”jšÊ
	SAFE_DELETE_ARRAY(_curves);

}

void AnimationNode::getData(Vector3D * position, Vector3D * angle, Vector3D * scale,Vector3D* qAxis,double* qValue,bool* useQuartanion,double time) const
{
	for (int i = 0; i < _curveNumber; ++i){
		Curve::Type type = _curves[i]->getType();
	
		double value = _curves[i]->getValue(time);
		if (type == Curve::ROTATION_Q) {
			QCurve* q = static_cast<QCurve*>(_curves[i]);
			*qAxis = q->getAxis();
			*qValue = value;
			*useQuartanion = true;
			continue;
		}
		switch (type)
		{
		case Curve::ROTATION_X:
			angle->x = value;
			break;
		case Curve::ROTATION_Y:
			angle->y = value;
			break;
		case Curve::ROTATION_Z:
			angle->z = value;
			break;
		case Curve::SCALE_X:
			scale->x = value;
			break;
		case Curve::SCALE_Y:
			scale->y = value;
			break;
		case Curve::SCALE_Z:
			scale->z = value;
			break;
		case Curve::TRANSLATION_X:
			position->x = value;
			break;
		case Curve::TRANSLATION_Y:
			position->y = value;
			break;
		case Curve::TRANSLATION_Z:
			position->z = value;
			break;
		case Curve::NONE:
			break;
		default:
			break;
		}
	}
}

const string * AnimationNode::getName() const
{
	return &_name;
}
