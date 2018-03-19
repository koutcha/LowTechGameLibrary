#include "Library\Sphere.h"
#include "GameLib\GameLib.h"
#include "GameLib\Math.h"
#include "Library\VertexBuffer.h"
#include "Library\IndexBuffer.h"
#include "Library\Vector3D.h"
#include "Library\Batch.h"
#include "Library\Matrix44.h"
#include "Library\Matrix34.h"
using namespace GameLib;
Sphere::Sphere(int n,double r) :
_position(0, 0, 0),
_angle(0, 0, 0),
_scale(1.0,1.0, 1.0),
_batch(0),
_vertex(0),
_index(0)
{
	int split = n;
	double radius = r;
	double theta = 360.0 / static_cast<double>(split);
	double sub =180.0;
	int layerNum = split / 2 - 1;
	int vertexNum = split*layerNum +2;
	VertexBuffer* vBuffer = new VertexBuffer(vertexNum);
	_vertex = vBuffer;
	IndexBuffer* iBuffer = new IndexBuffer((split*2+split*(layerNum-1)*2)*3);
	cout << (split * 2 + split*(layerNum - 1) * 2) * 3 << endl;
	_index = iBuffer;
	vBuffer->setPosition(0, Vector3D(0.0,r,0.0));
	vBuffer->setPosition(vertexNum - 1, Vector3D(0.0,-r,0.0));
	double x;
	double y;
	double z;
	double layersR;
	cout << theta << endl;
	for (int i = 0; i < layerNum; ++i) {
		y = r*GameLib::sin(90.0 + theta*(i + 1));
		layersR = r*abs(GameLib::cos(90.0 + theta*(i + 1)));
		for (int j = 0; j < split; ++j) {
			double dj = static_cast<double>(j);
			x = layersR*GameLib::sin(theta*dj);
			z = layersR*GameLib::cos(theta*dj);
			
			vBuffer->setPosition(i*split + j + 1, Vector3D(x, y, z));
		}
	}
	int top = 0;
	int bottom = vertexNum - 1;
	int tIndex = 0;
	
	for (int i = 1; i < split; ++i) {
		iBuffer->setTriangle(tIndex, top, i ,i+1);
		tIndex++;
		int isk = i;
		for (int k = 0; k < layerNum - 1; ++k) {
			isk = i + split*k;
			iBuffer->setTriangle(tIndex, isk, isk + split,isk+1);
			tIndex++;
			iBuffer->setTriangle(tIndex, isk + split + 1, isk + 1,isk+ split);
			tIndex++;
		}
		iBuffer->setTriangle(tIndex, bottom,bottom-split+i,bottom-split+i-1);
		tIndex++;
	}
	
	int first = 1;
	int last = split;
	iBuffer->setTriangle(tIndex, top,last,first);
	cout << tIndex << "(" << top << "," << first << "," <<last<< ")" << endl;
	tIndex++;
	for (int k = 0; k < layerNum - 1; ++k) {
		iBuffer->setTriangle(tIndex, last + k*split,last+split+split*k, first + k*split);
		cout << tIndex << "(" << last + k*split << "," << first + k*split << "," << last + split + split*k << ")" << endl;
		tIndex++;
		iBuffer->setTriangle(tIndex, first +split+ split*k, first+k*split, last + split + split*k);
		cout << tIndex << "(" << first + split + split*k<< "," << first + k*split << "," << last + split + split*k << ")" << endl;
		tIndex++;
	}

	iBuffer->setTriangle(tIndex, bottom, bottom-split, bottom - 1);
	_batch = new Batch(vBuffer, iBuffer, 0, GameLib::Framework::BlendMode::BLEND_OPAQUE);
}

Sphere::Sphere(bool isInverted):
	_position(0, 0, 0),
	_angle(0, 0, 0),
	_scale(1.0, 1.0, 1.0),
	_batch(0),
	_vertex(0),
	_index(0)
{
	int split = 50;
	double r = 1.0;
	double theta = 360.0 / static_cast<double>(split);
	double sub = 180.0;
	int layerNum = split / 2 - 1;
	int vertexNum = split*layerNum + 2;
	VertexBuffer* vBuffer = new VertexBuffer(vertexNum);
	_vertex = vBuffer;
	IndexBuffer* iBuffer = new IndexBuffer((split * 2 + split*(layerNum - 1) * 2) * 3);
	cout << (split * 2 + split*(layerNum - 1) * 2) * 3 << endl;
	_index = iBuffer;
	vBuffer->setPosition(0, Vector3D(0.0, r, 0.0));
	vBuffer->setPosition(vertexNum - 1, Vector3D(0.0, -r, 0.0));
	double x;
	double y;
	double z;
	double layersR;
	cout << theta << endl;
	for (int i = 0; i < layerNum; ++i) {
		y = r*GameLib::sin(90.0 + theta*(i + 1));
		layersR = r*abs(GameLib::cos(90.0 + theta*(i + 1)));
		for (int j = 0; j < split; ++j) {
			double dj = static_cast<double>(j);
			x = layersR*GameLib::sin(theta*dj);
			z = layersR*GameLib::cos(theta*dj);

			vBuffer->setPosition(i*split + j + 1, Vector3D(x, y, z));
		}
	}
	int top = 0;
	int bottom = vertexNum - 1;
	int tIndex = 0;

	for (int i = 1; i < split; ++i) {
		iBuffer->setTriangle(tIndex, top, i, i + 1);
		tIndex++;
		int isk = i;
		for (int k = 0; k < layerNum - 1; ++k) {
			isk = i + split*k;
			iBuffer->setTriangle(tIndex, isk, isk + split, isk + 1);
			tIndex++;
			iBuffer->setTriangle(tIndex, isk + split + 1, isk + split ,isk + 1);
			tIndex++;
		}
		iBuffer->setTriangle(tIndex, bottom, bottom - split + i - 1,bottom - split + i);
		tIndex++;
	}

	int first = 1;
	int last = split;
	iBuffer->setTriangle(tIndex, top, last, first);
	cout << tIndex << "(" << top << "," << first << "," << last << ")" << endl;
	tIndex++;
	for (int k = 0; k < layerNum - 1; ++k) {
		iBuffer->setTriangle(tIndex, last + k*split, last + split + split*k, first + k*split);
		cout << tIndex << "(" << last + k*split << "," << first + k*split << "," << last + split + split*k << ")" << endl;
		tIndex++;
		iBuffer->setTriangle(tIndex, first + split + split*k, first + k*split, last + split + split*k);
		cout << tIndex << "(" << first + split + split*k << "," << first + k*split << "," << last + split + split*k << ")" << endl;
		tIndex++;
	}

	iBuffer->setTriangle(tIndex, bottom, bottom - split, bottom - 1);
	_batch = new Batch(vBuffer, iBuffer, 0, GameLib::Framework::BlendMode::BLEND_OPAQUE);
}

Sphere::~Sphere()
{
	SAFE_DELETE(_batch);
	SAFE_DELETE(_index);
	SAFE_DELETE(_vertex);
}

Batch * Sphere::getBatch() const
{
	return _batch;
}

void Sphere::draw(const Matrix44 & projectionViewMatrix, const Vector3D & lightVector, const Vector3D & lightColor, const Vector3D & ambient, const Vector3D & diffuseColor) const
{
	Matrix34 wm;
	wm.setIdentity();
	_batch->draw(projectionViewMatrix,wm, lightVector, lightColor, ambient,diffuseColor);
}
