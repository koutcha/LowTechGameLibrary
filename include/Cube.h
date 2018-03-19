#ifndef CUBE_H
#define CUBE_H
class VertexBuffer;
class IndexBuffer;
class Batch;
class Vector3D;
class Matrix44;
class Matrix34;
class Cube {
private:
	VertexBuffer* _vb;
	IndexBuffer* _ib;
	Batch* _batch;

public:
	Cube(Vector3D size);
	~Cube();
	Batch* getBatch()const;
};
#endif