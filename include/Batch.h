#ifndef BATCH_H
#define BATCH_H
#include"GameLib\Framework.h"
#include <string>
using namespace std;
using namespace GameLib;
class MyTexture;
class VertexBuffer;
class IndexBuffer;
class Matrix34;
class Matrix44;
class Element;
class Vector3D;
class GraphicsDatabase;
class Quaternion;
class PointLight;
class Batch {
private:
	const VertexBuffer* vertexBuffer;
	const IndexBuffer* indexBuffer;
	const MyTexture* texture;
	Framework::BlendMode blendMode;

	Vector3D* normals;

	string name;
	void computeNormal(Vector3D * normals, const VertexBuffer & vb, const IndexBuffer & ib);

public :
	enum ShadingMode {
		GOURAND_SHADING,
		FLAT_SHADING
	};

	Batch(const VertexBuffer* vertexBuffer,
		const IndexBuffer* indexBuffer,
		const MyTexture* texture,
		Framework::BlendMode blendMode);
	Batch(const Element* e,const GraphicsDatabase* database);
	~Batch();
	//グーローシェーディングのときに頂点書換したら呼び出す
	void recomputeNormal();
	void setBlendMode(Framework::BlendMode blendMode);
	void draw(const Matrix44 & projectionViewMatrix, const Matrix34 & worldMatrix, const Vector3D & lightVector, const Vector3D & lightColor, const Vector3D & ambient, const Vector3D & diffuseColor, const Vector3D & specular, double spcularPow, const Vector3D & eyeVector,ShadingMode shader) const;
	void draw(const Matrix44 & projectionViewMatrix, const Matrix34 & worldMatrix,  const PointLight* lightSources,int lightNumber, const Vector3D & ambient, const Vector3D & diffuseColor, const Vector3D & specular, double spcularPow, const Vector3D & eyeVector, ShadingMode shader) const;
	const string* getName()const;
	const string* getDebugString() const;

};
#endif
