#ifndef CAMERA_H
#define CAMERA_H
#include "Vector3D.h"
class Matrix44;
class Camera {
private:
	Vector3D position;
	Vector3D target;
	double fieldOfViewY;
	double nearClip;
	double farClip;
public:
	Camera();
	~Camera();

	void setPosition(const Vector3D&);
	void setTarget(const Vector3D&);
	void setFieldOfView(double);
	void setNearClip(double);
	void setFarClip(double);

	const Vector3D getPosition() const;
	const Vector3D getTarget() const;
	double getFieldOfView() const;
	double getNearClip() const;
	double getFarClip() const;

	void createProjectionViewMatrix(Matrix44*) const;
};
#endif
