#include "Curve.h"
#include "Element.h"
#include "Attribute.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
Curve::Curve():
	_data(0),
	_dataNumber(0),
	_type(NONE)
{
}
Curve::Curve(const Element &e):
	_data(0),
	_dataNumber(0),
	_type(NONE)
{
	ASSERT(*e.getName() == "Curve");
	int an = e.getAttributeNumber();
	cout << "an:" << an << endl;
	for (int i = 0; i < an; ++i) {
		const Attribute* a = e.getAttribute(i);
		cout << a->getName()->c_str() << endl;
		if (*a->getName() == "type") {
			string aName = *a->getValue();
			if (aName == "rotationX") {
				_type = ROTATION_X;
			}
			else if (aName == "rotationY")
			{
				_type = ROTATION_Y;
			}
			else if (aName == "rotationZ") {
				_type = ROTATION_Z;
			}
			else if (aName == "translationX") {
				_type = TRANSLATION_X;
			}
			else if (aName == "translationY") {
				_type = TRANSLATION_Y;
			}
			else if (aName == "translatinZ") {
				_type = TRANSLATION_Z;
			}
			else if (aName == "scaleX") {
				_type = SCALE_X;
			}
			else if (aName == "scaleY") {
				_type = SCALE_Y;
			}
			else if (aName == "scaleZ") {
				_type = SCALE_Z;
			}
		}
	}
	int cn = e.getChildNumber();
	_data = new Data[cn];

	_dataNumber = cn;
	cout <<cn << endl;
	for (int k = 0; k < cn; ++k) {
		const Element* child = e.getChild(k);
		int cattributeNum = child->getAttributeNumber();

		if (*child->getName() == "Data") {
			for (int j = 0; j < cattributeNum; ++j) {
				const Attribute* a = child->getAttribute(j);
				if (*a->getName() == "time") {
					cout << a->getDoubleValue() << endl;
					cout << _data[k]._time << endl;
					_data[k]._time = a->getDoubleValue();
				}
				else if (*a->getName() == "value") {
					_data[k]._value = a->getDoubleValue();
				}
			}
		}
	}
}


Curve::~Curve()
{
	SAFE_DELETE_ARRAY(_data);
}

const double Curve::getValue(double time) const
{
	//‚à‚¤‚¿‚å‚¢ŠÈ—ª‰»‚Å‚«‚»‚¤
	time = fmod(time, _data[_dataNumber - 1]._time);
	double t1, t0,p1,p0;
	for (int i = 0; i < _dataNumber-1; ++i) {
		if (_data[i]._time <= time && time < _data[i+1]._time) {
			t1 = _data[i + 1]._time;
			t0 = _data[i]._time;
			p1 = _data[i + 1]._value;
			p0 = _data[i]._value;
			time = (time - t0) / (t1 - t0);
			return (p1 - p0)*time + p0;
		}
	}
	return 0;
}

Curve::Type Curve::getType() const
{
	return _type;
}


Curve::Data::Data()
{
}
