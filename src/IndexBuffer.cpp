#include "IndexBuffer.h"
#include "GameLib\GameLib.h"
#include "Element.h"
#include "Attribute.h"
using namespace GameLib;
IndexBuffer::IndexBuffer(int size):size(size)	
{
	indices = new unsigned[size];
}

IndexBuffer::IndexBuffer(const Element * e)
{
	name = *e->getAttribute(0)->getValue();
	int triangleSize = e->getChildNumber();
	size= triangleSize * 3;
	indices = new unsigned[size];
	for (int i = 0; i < triangleSize; ++i) {
		const Element* triangle = e->getChild(i);
		if (*triangle->getName() == "Triangle") {
			if (*triangle->getAttribute(0)->getName() == "indices") {
				cout << "start get Index" << endl;
				int indices3[3];
				triangle->getAttribute(0)->getIntValues(indices3, 3);
				indices[i * 3] = (unsigned)indices3[0];
				indices[i * 3 + 1] = (unsigned)indices3[1];
				indices[i * 3 + 2] = (unsigned)indices3[2];
			}
		}
	}
}

IndexBuffer::~IndexBuffer()
{
	SAFE_DELETE_ARRAY(indices);
}

unsigned IndexBuffer::getIndex(int i) const
{
	if (i >= size || i<0) {
		HALT("out of Index");
	}
	return indices[i];
}

void IndexBuffer::setIndex(int i, unsigned value)
{
	if (i >= size || i<0) {
		HALT("out of Index");
	}
	indices[i] = value;
}
void IndexBuffer::setTriangle(int triangleIndex, int i0, int i1, int i2) {
	ASSERT(0 <= triangleIndex * 3|| triangleIndex*3 < size);
	//cout << i0 << ":" << i1 <<":"<< i2 << endl;
	indices[3 * triangleIndex] = i0;
	indices[3 * triangleIndex + 1] = i1;
	indices[3 * triangleIndex + 2] = i2;
}
void IndexBuffer::reverseTriangle(int triangleIndex)
{
	ASSERT(0 <= triangleIndex * 3 || triangleIndex * 3 < size);
	int sub = indices[3 * triangleIndex];
	indices[3 * triangleIndex] = indices[3 * triangleIndex + 1];
	indices[3 * triangleIndex + 1] = sub;
}
int IndexBuffer::getSize() const
{
	return size;
}

const string * IndexBuffer::getName() const
{
	return &name;
}

const string * IndexBuffer::getDebugString() const
{
	string* str = new string();
	*str += "indexList\n" ;
	for (int i = 0; i < size; ++i) {
		if (i % 3 == 0) {
			*str += '\n';
		}
		*str += to_string(indices[i]) + ',';
	}
	return str;
}
