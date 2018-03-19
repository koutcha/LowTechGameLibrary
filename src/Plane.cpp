#include "Plane.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Batch.h"
#include "GameLib\Framework.h"
#include "GameLib\GameLib.h"
#include "Vector3D.h"

using namespace GameLib;

Plane::Plane(int splitNum,double size)
{
	int vertexWidth = splitNum + 1;
	int vertexDepth = splitNum + 1;
	int indexSize = vertexWidth * vertexDepth;
	_vb = new VertexBuffer(indexSize);
	_ib = new IndexBuffer(splitNum*splitNum * 6);
	int count = 0;
	Vector3D point(-size / 2.0, 0.0, -size / 2.0);

	double addWidth = size / splitNum;
	for (int i = 0; i < vertexDepth; ++i) {
		for (int j = 0; j < vertexWidth; ++j) {
			_vb->setPosition(i*vertexWidth + j, point);
			point.x += addWidth;
			count++;
		}
		point.z += addWidth;
		point.x = -size / 2.0;
	}

	

	count = 0;
	for (int i = 0; i < vertexDepth - 1; ++i) {
		for (int j = 0; j < vertexWidth - 1; ++j) {

			_ib->setTriangle(count, i*vertexWidth + j, (i + 1)*vertexWidth + j, i*vertexWidth + j + 1);
			count++;
			_ib->setTriangle(count, (i + 1)*vertexWidth + j + 1, i*vertexWidth + j + 1, (i + 1)*vertexWidth + j);
			count++;
		}
	}

	_batch = new Batch(_vb, _ib, 0, GameLib::Framework::BlendMode::BLEND_OPAQUE);

}


Plane::~Plane()
{
	SAFE_DELETE(_batch);
	SAFE_DELETE(_ib);
	SAFE_DELETE(_vb)
}

Batch * Plane::getBatch() const
{
	return _batch;
}