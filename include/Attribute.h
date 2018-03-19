#ifndef MYATTRIBUTE_H
#define MYATTRIBUTE_H
#include<string>
using namespace std;
class Attribute {
private:
	string name;
	string value;
public:
	Attribute(const char* name,const char* value);
	~Attribute();
	const string* getName() const;
	const string* getValue() const;
	
	int getIntValue() const;
	double getDoubleValue() const;
	void getIntValues(int* out,int outSize)const;
	void getDoubleValues(double* out,int outSize)const;
};
#endif
