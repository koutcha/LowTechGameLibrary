#ifndef QCURVE_H
#define QCURVE_H
#include "Curve.h"
class Element;
//�N�I�[�^�j�I����p���
class QCurve:public Curve {
public:
	Vector3D rotationAxis;
	QCurve(const Element&);
	~QCurve();
	Vector3D getAxis()const override;
private:

};
#endif // !QCURVE_H

