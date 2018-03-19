#ifndef PLANE_MODEL_H
#define PLANE_MODEL_H

class VertexBuffer;
class IndexBuffer;
class Batch;

class Plane
{
public:
	Plane(int splitNumber,double size);
	~Plane();
	Batch* getBatch()const;
private:
	VertexBuffer * _vb;
	IndexBuffer* _ib;
	Batch* _batch;
};
#endif
