#include "QCurve.h"
#include "Element.h"
#include "Attribute.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
QCurve::QCurve(const Element &e)
{   
	//Curve()実行

	//Curveとほぼ同じ処理
	ASSERT(*e.getName() == "QCurve");

	_type = ROTATION_Q;
	int an = e.getAttributeNumber();
	//setAxis
	for (int i = 0; i < an; ++i) {
		Attribute a = *e.getAttribute(i);
		if (*a.getName() == "axis") {
			a.getDoubleValues(&rotationAxis.x, 3);
		}
	}

	int cn = e.getChildNumber();
	_data = new Data[cn];

	_dataNumber = cn;
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

QCurve::~QCurve()
{
	//virtual ~Curve() でデータを破棄
}

Vector3D QCurve::getAxis() const
{
	return rotationAxis;
}


