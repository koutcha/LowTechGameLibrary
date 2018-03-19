#include "Cube.h"
#include "Vector3D.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "GameLib\Framework.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Batch.h"
using namespace GameLib;
Cube::Cube(Vector3D size) :
	_vb(0),
	_ib(0),
	_batch(0)
{
	_vb = new VertexBuffer(8);
	double subX = -size.x / 2;
	double subY = -size.y / 2;
	double subZ = -size.z / 2;
	double xw = size.x / 2;
	double yh = size.y / 2;
	double zd = size.z / 2;

	_vb->setPosition(0,Vector3D(subX, yh, zd));
	_vb->setPosition(1,Vector3D(xw, yh, zd));
	_vb->setPosition(2,Vector3D(subX, subY, zd));
	_vb->setPosition(3,Vector3D(xw, subY, zd));

	_vb->setPosition(4,Vector3D(subX, yh, subZ));
	_vb->setPosition(5,Vector3D(xw, yh, subZ));
	_vb->setPosition(6,Vector3D(subX, subY, subZ));
	_vb->setPosition(7,Vector3D(xw, subY, subZ));

	int index[36] = {
		0,1,2,//+z
		3,2,1,
		4,5,6,//-z
		7,6,5,
		3,7,1,//+x
		5,1,7,
		0,4,2,//-x
		6,2,4,
		4,0,5,//+y
		1,5,0,
		6,2,7,//-y
		3,7,2

	};
	_ib = new IndexBuffer(36);
	for (int i = 0; i < 36; ++i) {
		_ib->setIndex(i, index[i]);
	}
	_batch = new  Batch(_vb, _ib, 0, Framework::BLEND_OPAQUE);
}
Cube::~Cube()
{
	SAFE_DELETE(_ib);
	SAFE_DELETE(_vb);
	SAFE_DELETE(_batch);
}

Batch * Cube::getBatch() const
{
	return _batch;
}