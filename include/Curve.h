#ifndef CURVE_H
#define CURVE_H
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
	~Curve();
	const double getValue(double)const;
	Type getType()const;

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