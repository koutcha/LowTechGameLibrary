#ifndef CURVE_H
#define CURVE_H
#include "Vector3D.h"
class Element;
class Curve {
public:
	enum Type {
		ROTATION_X,
		ROTATION_Y,
		ROTATION_Z,
		SCALE_X,
		SCALE_Y,
		SCALE_Z,
		TRANSLATION_X,
		TRANSLATION_Y,
		TRANSLATION_Z,
		ROTATION_Q,
		NONE
	};
	Curve();
	Curve(const Element&);
	virtual ~Curve();
	const double getValue(double)const;
	Type getType()const;
	virtual Vector3D getAxis() const { return Vector3D(0, 0, 0); };
protected:
	struct Data
	{
	public:
		Data();
		 double _time;
		 double _value;
	}; 
	
	Data* _data;
	int _dataNumber;
	Type _type;
};
#endif