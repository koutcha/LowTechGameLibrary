#ifndef STAGE_H
#define STAGE_H
class Vector3D;
class Model;
class Matrix44;
class GraphicsDatabase;
class Stage {
private:
	Model* _model;
public:
	Stage();
	~Stage();
	void draw(Matrix44& pvm);
};
#endif