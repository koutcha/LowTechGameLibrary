#ifndef QCURVE_H
#define QCURVE_H
#include "Vector3D.h"
#include "Curve.h"
class Element;
//�N�I�[�^�j�I����p���
class QCurve:public Curve {
public:
	Vector3D rotationAxis;
	QCurve(const Element&);
	~QCurve();
	Vector3D getAxis()const;
private:
};
#endif // !QCURVE_H

