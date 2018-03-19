#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include<string>
using namespace std;
class Vector3D;
class Vector2D;
class Element;
class VertexBuffer {
private:
	Vector3D* positions;
	Vector2D* UVs;
	string name;
	int size;
public:
	explicit VertexBuffer(int size);
	VertexBuffer(const Element* e);
	~VertexBuffer();
	const Vector3D* getPosition(int i) const;
	const Vector2D* getUV(int i)const;
	void setPosition(int i, const Vector3D& position);
	void setUV(int i, const Vector2D& uv);
	int getSize()const;
	const string* getName() const;
	const string* getDebugString() const;
};
#endif

