#include "VertexBuffer.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "Attribute.h"
#include "Element.h"
#include "GameLib\/GameLib.h"
using namespace GameLib;
VertexBuffer::VertexBuffer(int size):size(size)
{
	positions = new Vector3D[size];
	UVs = new Vector2D[size];
}

VertexBuffer::VertexBuffer(const Element* e):
positions(0),
UVs(0)
{
	//ƒRƒs[
	name = *e->getAttribute(0)->getValue();
	size = e->getChildNumber();
	cout << "VertexChildren:" << size << endl;
	positions = new Vector3D[size];
	UVs = new Vector2D[size];
	
	for (int i = 0; i < size; ++i) {
		cout << "child" << i << endl;
		const Element* vertexElement = e->getChild(i);
		int attributeNum = vertexElement->getAttributeNumber();

		for (int j = 0; j < attributeNum; ++j) {
			const string name = *vertexElement->getAttribute(j)->getName();
			cout  <<"getName" << endl;
			if (name == "position") {
				cout << "true" << endl;
			}
			else {
				cout << "false" << endl;
			}
			if (name == "position") {
				cout << "loadPos" <<endl;
				vertexElement->getAttribute(j)->getDoubleValues(&positions[i].x, 3);
				cout << "loadPosEnd" << endl;
			}
			else if (name == "uv") {
				cout << "loaduv" << endl;
				vertexElement->getAttribute(j)->getDoubleValues(&UVs[i].x, 2);
			}
		}
		cout << endl;
	}
}

VertexBuffer::~VertexBuffer()
{
	SAFE_DELETE_ARRAY(positions);
	SAFE_DELETE_ARRAY(UVs);
}

const Vector3D * VertexBuffer::getPosition(int i) const
{
	if (i >= size || i<0) {
		cout << i << ":getPoutofIndex" << endl;
		HALT("out of Index" + i);
	}
	return positions + i;
}

const Vector2D * VertexBuffer::getUV(int i) const
{
	if (i >= size || i<0) {
		cout << i << endl;
		HALT("getUV:out of Index");
	}
	return UVs + i;
}

void VertexBuffer::setPosition(int i, const Vector3D & position)
{
	if (i >= size || i<0) {
		cout << i << ":setPoutofIndex" << endl;
		HALT("out of Index");
	}
	positions[i] = position;
}

void VertexBuffer::setUV(int i, const Vector2D & uv)
{
	if (i >= size || i<0) {
		cout << i << endl;
		HALT("setUV:out of Index");
	}
	UVs[i] = uv;
}

int VertexBuffer::getSize() const
{
	return size;
}

const string * VertexBuffer::getName() const
{
	return &name;
}

const string * VertexBuffer::getDebugString() const
{
	string* str = new string();
	*str += "vartex     uv\n";
	for (int i = 0; i < size; ++i) {
		*str += to_string(positions[i].x) + ','
			+ to_string(positions[i].y) + ','
			+ to_string(positions[i].z) + ')' + '\n';

	}
	return str;
}
