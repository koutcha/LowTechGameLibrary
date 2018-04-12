#include "Attribute.h"
#include "GameLib\GameLib.h"
#include <vector>
using namespace GameLib;
Attribute::Attribute(const char * name, const char * value)
{
	this->name = name;
	this->value = value;
}

Attribute::~Attribute()
{
	cout << "デストラクト" << name.c_str()<< "="<<value.c_str() << endl;
}

const string * Attribute::getName() const
{
	return &name;
}

const string * Attribute::getValue() const
{
	return &value;
}

int Attribute::getIntValue() const
{
	return stoi(value);
}

double Attribute::getDoubleValue() const
{
	return stod(value);
}

void Attribute::getIntValues(int * out,int outSize) const
{
	vector<string> values(10);
	string element;
	int outCount = 0;
	for (unsigned i = 0; i < value.size(); i++) {
		if (value[i] == ',') {
			values[outCount] = element;
			element.clear();
			outCount++;
		}
		else {
			element += value[i];
		}		
	}
	values[outCount] = element;
	for (int i = 0; i < outSize; i++) {
		out[i] = stoi(values[i]);
		cout << "out" << out[i] << endl;
	}
}

void Attribute::getDoubleValues(double * out,int outSize) const
{
	vector<string> values(10);
	string element;
	int outCount = 0;
	for (unsigned i = 0; i < value.size(); i++) {
		if (value[i] == ',') {
			values[outCount] = element;
			element.clear();
			outCount++;
		}
		else {
			element += value[i];
		}
	}
	values[outCount] = element;
	for (int i = 0; i < outSize; i++) {
		out[i] = stod(values[i]);
		cout << "out" << out[i] << endl;
	}

}
