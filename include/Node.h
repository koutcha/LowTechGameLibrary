#ifndef ANIMETION_NODE_H
#define ANIMATION_NODE_H
#include "Vector3D.h"
#include "Batch.h"
#include<string>

using namespace std;
class Batch;
class Matrix44;
class Matrix34;
class AnimationNode;
class Node {
private:

	Node** _children;
	unsigned _childrenNumber;
	const Batch* _batch;
	Vector3D _position;
	Vector3D _angle;
	Vector3D _rotationAxis;
	double _qAngle;
	bool _useQuaternion;
	Vector3D _scale;
	Vector3D _color;
	//スペキュラの色,係数
	Vector3D _specular;
	double _specularPow;
	string _name;
	Batch::ShadingMode _shader;
public:
	Node();
	Node(const Batch* batch, int chilerenNumber);
	~Node();
	void draw(const Matrix44 & projectionViewMatrix, const Matrix34 & worldMatrix, const Vector3D & lightVector, const Vector3D & lightColor, const Vector3D & ambient, const Vector3D & eyePosition)const;
	void draw(const Matrix44 & projectionViewMatrix, const Matrix34 & worldMatrix, const PointLight* lightSources, int lightNumber, const Vector3D & ambient, const Vector3D & eyeVector) const;
	void setTranslation(const Vector3D&);
	void setRotation(const Vector3D&);
	void setQuaternionRotation(const Vector3D& axis,double angle);
	void setScale(const Vector3D&);

	void setBatch(const Batch&);

	//setDiffuseColor
	void setColor(const Vector3D&);

	void setSpecular(const Vector3D&,double specularPow);
	void setShader(Batch::ShadingMode shader);
	void setName(const char* name);
	void setChild(int index, Node*);
	void setChildNumber(int childNum);
	void update(double, const AnimationNode&);

	const Batch* getBatch()const;
	const Vector3D* getTranslation()const;
	const Vector3D* getRotation()const;
	const Vector3D* getScale()const;
	const string* getName()const;
	Batch::ShadingMode getShader()const;
	void writeChildrenConsole() const;
	
};
#endif
