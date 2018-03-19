#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include <string>
using namespace std;

class Element;

class IndexBuffer {
private:
	unsigned* indices;
	string name;
	int size;
public:
	IndexBuffer(int size);
	IndexBuffer(const Element* e);
	~IndexBuffer();
	unsigned getIndex(int i)const;
	void setIndex(int i, unsigned value);
	void setTriangle(int triangleIndex, int i0, int i1, int i2);
	void reverseTriangle(int triangleIndex);
	int getSize()const;
	const string* getName()const;
	const string*getDebugString()const;
};
#endif