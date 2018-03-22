#include "Batch.h"
#include "PointLight.h"
#include "GameLib\GameLib.h"
#include "GameLib\Framework.h"
#include "Matrix34.h"
#include "Matrix44.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Element.h"
#include "Attribute.h"
#include "Texture.h"
#include "GraphicsDatabase.h"
#include "Quaternion.h"
#include "Matrix33.h"
#include <sstream>
using namespace std;
using namespace GameLib;
static const unsigned MAX_LIGHT_NUM = 4;
double clamp01(double value) {
	if (value < 0.0) {
		return 0.0;
	}
	else if (value >1.0) {
		return 1.0;
	}
	else {
		return value;
	}
}
unsigned lighting(
	const Vector3D& lightVector,
	const Vector3D& lightColor,
	const Vector3D& ambient,
	const Vector3D& diffuseColor,
	const Vector3D& specular,
	double speclarPow,
	const Vector3D& eyeVector,
	const Vector3D& normal)
{
	Vector3D color;
	Vector3D normalLight;
	
	normalLight = lightVector;
	//normalLight *= -1.0;
	normalLight.normalize();
	double cosine = normal.dot(normalLight);


	//視点ベクトル（視線に頂点位置は関係ない）
	Vector3D toEye = eyeVector;
	toEye *= -1.0;
	//正規化
	toEye.normalize();
	//ハーフベクトル
	Vector3D half;
	half.setAdd(toEye, normalLight);
	half.normalize();
	//反射光のコサイン
	double cosineSpecular = normal.dot(half);

	cosineSpecular = pow(clamp01(cosineSpecular),speclarPow);
	
	if (cosine < 0.0) {
		cosine = 0.0;
	}
	color.x = lightColor.x*diffuseColor.x*cosine +	specular.x*cosineSpecular+ ambient.x;
    color.y = lightColor.y*diffuseColor.y*cosine + specular.y*cosineSpecular + ambient.y;
	color.z = lightColor.z*diffuseColor.z*cosine + specular.z*cosineSpecular + ambient.z;

	color.x = clamp01(color.x);
	color.y = clamp01(color.y);
	color.z = clamp01(color.z);
	int r = static_cast<int>(color.x*255.0 + 0.5);
	int g = static_cast<int>(color.y*255.0 + 0.5);
	int b = static_cast<int>(color.z*255.0 + 0.5);
	return 0xff000000 | (r << 16) | (g << 8) | b;
}


unsigned lightingWithPointLight(
	const PointLight* lightResorces,
	int lightNumber,
	const Vector3D& ambient,
	const Vector3D& diffuseColor,
	const Vector3D& normal,
	const Vector3D& vertexPositon) {

	Vector3D color(0, 0, 0);
	Vector3D normalLight;
	Vector3D colorSum(0,0,0);
	for (int i = 0; i < lightNumber; ++i) {
		normalLight.setSub(lightResorces[i].getPosition(), vertexPositon);
		double d = normalLight.length()*normalLight.length();
		normalLight.normalize();
		double cosine = normal.dot(normalLight);
		if (cosine < 0.0) {
			cosine = 0.0;
		}
		Vector3D lightColor = lightResorces[i].getColor();
		cosine /= d;

		lightColor *= cosine;
		colorSum += lightColor;
	}



	color.x = colorSum.x*diffuseColor.x + ambient.x;
	color.y = colorSum.y*diffuseColor.y + ambient.y;
	color.z = colorSum.z*diffuseColor.z + ambient.z;

	color.x = clamp01(color.x);
	color.y = clamp01(color.y);
	color.z = clamp01(color.z);
	int r = static_cast<int>(color.x*255.0 + 0.5);
	int g = static_cast<int>(color.y*255.0 + 0.5);
	int b = static_cast<int>(color.z*255.0 + 0.5);
	return 0xff000000 | (r << 16) | (g << 8) | b;
}

Batch::Batch(const VertexBuffer * vertexBuffer, const IndexBuffer * indexBuffer, const MyTexture * texture, Framework::BlendMode blendMode):
vertexBuffer(vertexBuffer),
indexBuffer(indexBuffer),
texture(texture),
blendMode(blendMode)
{
	normals = new Vector3D[vertexBuffer->getSize()];
	computeNormal(normals, *vertexBuffer, *indexBuffer);
}

Batch::Batch(const Element * e,const GraphicsDatabase* database):
	vertexBuffer(0),
	indexBuffer(0),
	texture(0),
	blendMode(Framework::BLEND_OPAQUE)

{
	int attributeNum = e->getAttributeNumber();
	for (int i = 0; i < attributeNum; ++i) {
		const string attributeName = *e->getAttribute(i)->getName();
		const string attributeValue = *e->getAttribute(i)->getValue();
		if (attributeName == "name") {
			name = attributeValue;
		}
		else if (attributeName == "vertexBuffer") {
			vertexBuffer = database->getVertexBuffer(attributeValue.c_str());
			if (!vertexBuffer) {
				HALT("vertex:nohit");
			}
		}
		
		else if (attributeName == "indexBuffer") {
			indexBuffer = database->getIndexBuffer(attributeValue.c_str());
		}
		else if (attributeName == "texture") {
			texture = database->getTexture(attributeValue.c_str());
		}
		else if (attributeName == "blendMode") {
			if (attributeValue == "opaque") {
				blendMode = Framework::BLEND_OPAQUE;
			}
			else if (attributeValue == "additive") {
				blendMode = Framework::BLEND_ADDITIVE;
			}
			else if (attributeValue == "linear") {
				blendMode = Framework::BLEND_LINEAR;
			}
		}
	}
	normals = new Vector3D[vertexBuffer->getSize()];
	computeNormal(normals, *vertexBuffer, *indexBuffer);
}



Batch::~Batch()
{
vertexBuffer = 0;
indexBuffer = 0;
texture = 0;
SAFE_DELETE_ARRAY(normals);
}

void Batch::recomputeNormal()
{
	computeNormal(normals, *vertexBuffer, *indexBuffer);
}

void Batch::setBlendMode(Framework::BlendMode blendMode)
{
	this->blendMode = blendMode;
}


void Batch::draw(const Matrix44 & projectionViewMatrix, 
	const Matrix34 & worldMatrix, 
	const Vector3D & lightVector, 
	const Vector3D & lightColor, 
	const Vector3D & ambient, 
	const Vector3D & diffuseColor, 
	const Vector3D &specular,
	double specularPow,
	const Vector3D & eyeVector,
	ShadingMode shader) const
{
	Framework f = Framework::instance();
	if (texture) {
		texture->set();
	}
	else {
		f.setTexture(0); //空のテクスチャ
	}
	Matrix44 pvwm;
	pvwm.setMul(projectionViewMatrix, worldMatrix);

	f.setBlendMode(blendMode);

	if (blendMode == Framework::BLEND_OPAQUE) {
		f.enableDepthWrite(true);
	}
	else {
		f.enableDepthWrite(false);
	}
	f.enableDepthTest(true);
	int vertexSize = vertexBuffer->getSize();
	//ワールド
	Vector3D* wv = new Vector3D[vertexSize];
	for (int i = 0; i < vertexSize; ++i) {
		worldMatrix.multiply(&wv[i], *vertexBuffer->getPosition(i));
	}
	double* fp4 = new double[vertexSize * 4];
	for (int i = 0; i < vertexSize; ++i) {
		pvwm.multiply(&fp4[i * 4], *vertexBuffer->getPosition(i));
	}
	//Matrix33 invtWm;
	//invtWm.setReductionTransInverse(worldMatrix);
	Matrix33 invM;
	invM.setReductionInverse(worldMatrix);
	Matrix33 invTransWm;
	invTransWm.setReductionTransInverse(worldMatrix);
	if (shader == Batch::FLAT_SHADING) {
		int triangleNumber = indexBuffer->getSize() / 3;
		for (int i = 0; i < triangleNumber; ++i) {
			int i0 = indexBuffer->getIndex(3 * i);
			int i1 = indexBuffer->getIndex(3 * i + 1);
			int i2 = indexBuffer->getIndex(3 * i + 2);
			Vector3D p01, p02;

			p01.setSub(wv[i1],wv[i0]);
			p02.setSub(wv[i2],wv[i0]);

			Vector3D normal;
			normal.setCross(p01, p02);
			normal.normalize();
			unsigned c = lighting(
				lightVector,
				lightColor,
				ambient,
				diffuseColor,
				specular,
				specularPow,
				eyeVector,
				normal);


			f.drawTriangle3DH(&fp4[i0 * 4], &fp4[i1 * 4], &fp4[i2 * 4], &vertexBuffer->getUV(i0)->x, &vertexBuffer->getUV(i1)->x, &vertexBuffer->getUV(i2)->x,c,c,c);
		}
	}
	else if(shader == Batch::GOURAND_SHADING)
	{

		Matrix34 wmNormal = worldMatrix; //法線の変換なので回転と拡大だけ
		wmNormal.m03 = wmNormal.m13 = wmNormal.m23 = 0.0;
		Vector3D invLight;
		invM.multiply(&invLight, lightVector);
		Vector3D invEye;
		invM.multiply(&invEye, eyeVector);
		unsigned* colors = new unsigned[vertexSize];
		//頂点ごとに色の計算
		for (int i = 0; i < vertexSize; ++i) {
			Vector3D worldNormal;
			
			invTransWm.multiply(&worldNormal, normals[i]);
			worldNormal.normalize();
			colors[i] = lighting(
				lightVector, 
				lightColor,
				ambient,
				diffuseColor,
				specular,
				specularPow,
				eyeVector,
				worldNormal);
		}
		int triangleNumber = indexBuffer->getSize() / 3;
		for (int i = 0; i < triangleNumber; ++i) {
			int i0 = indexBuffer->getIndex(3 * i);
			int i1 = indexBuffer->getIndex(3 * i + 1);
			int i2 = indexBuffer->getIndex(3 * i + 2);

			f.drawTriangle3DH(&fp4[i0 * 4], &fp4[i1 * 4], &fp4[i2 * 4], &vertexBuffer->getUV(i0)->x, &vertexBuffer->getUV(i1)->x, &vertexBuffer->getUV(i2)->x, colors[i0], colors[i1], colors[i2]);
			
		}
		SAFE_DELETE_ARRAY(colors);
	}

	SAFE_DELETE_ARRAY(fp4);
	SAFE_DELETE_ARRAY(wv);

}
void Batch::draw(
	const Matrix44 & projectionViewMatrix, 
	const Matrix34 & worldMatrix, 
	const PointLight * lightSources, 
	int lightNumber, 
	const Vector3D & ambient,
	const Vector3D & diffuseColor, 
	const Vector3D & specular,
	double spcularPow,
	const Vector3D & eyeVector,
	ShadingMode shader) const
{
	Framework f = Framework::instance();
	if (texture) {
		texture->set();
	}
	else {
		f.setTexture(0); //空のテクスチャ
	}
	Matrix44 pvwm;

	pvwm.setMul(projectionViewMatrix, worldMatrix);
	f.setBlendMode(blendMode);

	if (blendMode == Framework::BLEND_OPAQUE) {
		f.enableDepthWrite(true);
	}
	else {
		f.enableDepthWrite(false);
	}
	f.enableDepthTest(true);
	int vertexSize = vertexBuffer->getSize();
	//ワールド
	Vector3D* wv = new Vector3D[vertexSize];
	for (int i = 0; i < vertexSize; ++i) {
		worldMatrix.multiply(&wv[i], *vertexBuffer->getPosition(i));
	}
	double* fp4 = new double[vertexSize * 4];
	for (int i = 0; i < vertexSize; ++i) {
		pvwm.multiply(&fp4[i * 4], *vertexBuffer->getPosition(i));
	}

	if (shader == Batch::FLAT_SHADING) {
		int triangleNumber = indexBuffer->getSize() / 3;
		for (int i = 0; i < triangleNumber; ++i) {
			int i0 = indexBuffer->getIndex(3 * i);
			int i1 = indexBuffer->getIndex(3 * i + 1);
			int i2 = indexBuffer->getIndex(3 * i + 2);

			Vector3D p01, p02, p03;

			p01.setSub(wv[i1], wv[i0]);
			p02.setSub(wv[i2],wv[i0]);
			//面の中心
			p03 = wv[i0];
			p03 += wv[i1];
			p03 += wv[i2];
			p03 *= 0.333333333;
			//法線
			Vector3D normal;
			normal.setCross(p01, p02);
			normal.normalize();
			

			unsigned c = lightingWithPointLight(lightSources, lightNumber, ambient, diffuseColor, normal, p03);
			f.drawTriangle3DH(&fp4[i0 * 4], &fp4[i1 * 4], &fp4[i2 * 4], &vertexBuffer->getUV(i0)->x, &vertexBuffer->getUV(i1)->x, &vertexBuffer->getUV(i2)->x, c, c, c);
		}
	}
	else if (shader == Batch::GOURAND_SHADING)
	{

		Matrix34 wmNormal = worldMatrix; //法線の変換なので回転と拡大だけ
		wmNormal.m03 = wmNormal.m13 = wmNormal.m23 = 0.0;
		unsigned* colors = new unsigned[vertexSize];
		//頂点ごとに色の計算
		for (int i = 0; i < vertexSize; ++i) {
			Vector3D wNormal;
			wmNormal.multiply(&wNormal, normals[i]);
			wNormal.normalize();
			colors[i] = lightingWithPointLight(lightSources, lightNumber, ambient, diffuseColor, wNormal, wv[i]);
		}
		int triangleNumber = indexBuffer->getSize() / 3;
		for (int i = 0; i < triangleNumber; ++i) {
			int i0 = indexBuffer->getIndex(3 * i);
			int i1 = indexBuffer->getIndex(3 * i + 1);
			int i2 = indexBuffer->getIndex(3 * i + 2);

			f.drawTriangle3DH(&fp4[i0 * 4], &fp4[i1 * 4], &fp4[i2 * 4], &vertexBuffer->getUV(i0)->x, &vertexBuffer->getUV(i1)->x, &vertexBuffer->getUV(i2)->x, colors[i0], colors[i1], colors[i2]);

		}
		SAFE_DELETE_ARRAY(colors);
	}

	SAFE_DELETE_ARRAY(fp4);
	SAFE_DELETE_ARRAY(wv);


}

void Batch::computeNormal(
	Vector3D* normals,
	const VertexBuffer& vb,
	const IndexBuffer& ib) {
	for (int i = 0; i < vb.getSize(); ++i) {
		normals[i].set(0.0, 0.0, 0.0);
	}

	int triangleNumber = ib.getSize() / 3;
	for (int i = 0; i < triangleNumber; ++i) {
		unsigned i0 = ib.getIndex(i * 3);
		unsigned i1 = ib.getIndex(i * 3 + 1);
		unsigned i2 = ib.getIndex(i * 3 + 2);
		Vector3D n;
		Vector3D p01, p02;
		p01.setSub(*vb.getPosition(i1),*vb.getPosition(i0));
		p02.setSub(*vb.getPosition(i2), *vb.getPosition(i0));
		n.setCross(p01, p02);
		n.normalize();

		normals[i0] += n;
		normals[i1] += n;
		normals[i2] += n;

	}
	for (int i = 0; i < vb.getSize(); ++i) {
		normals[i].normalize();
	}
}

const string * Batch::getName() const
{
	return &name;
}

const string * Batch::getDebugString() const
{
	string* str = new string();
	*str += "vertexBuf:" + *vertexBuffer->getName() +'\n';
	*str += "indexBuf:" + *indexBuffer->getName() + '\n';
	if (texture) {
		*str += "tex:" + *texture->getName() + '\n';
	}
	*str += "blendMode:" + to_string(blendMode) + '\n';
	return str;
}
