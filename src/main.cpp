#include "GameLib\Framework.h"
#include "GameLib/Input/Manager.h"
#include "GameLib/Input/Keyboard.h"
#include "GameLib/Math.h"
#include <sstream>
#include "Image.h"
#include "Matrix44.h"
#include "Matrix34.h"
#include "Vector2D.h"
#include "Vector3D.h"
#include "Cube.h"
#include "Rectangle.h"
#include "Stage.h"
#include "Robo.h"
#include "JoyPad.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Batch.h"
#include "Model.h"
#include "Tree.h"
#include "GraphicsDatabase.h"
#include "Node.h"
#include "Texture.h"
using namespace std;
using namespace GameLib;

double pangle;
double subaaa;
double ppos;
double eyeZoom;


Robo* roboaa[2];
Model* stageaa;
GraphicsDatabase* ggd;
bool gFirstFrame = true;
VertexBuffer* gVertexBuffer;
IndexBuffer* gIndexBuffer;
MyTexture* gTexture;
Batch* gBatch;
Camera* gCamera;
int gCount;

Vector3D lightVector(0.0,1.0, -1.0);
Vector3D ambient(0.4, 0.4, 0.4);
Vector3D lightColor(1.0, 1.0, 1.0);


void Framework::update() {
	setFrameRate(60);
	if (gFirstFrame) {
		cout << "===loadData===="  << endl;
		ggd = new GraphicsDatabase("robo.txt");
		
		roboaa[0] = new Robo(0, ggd->createModel("robo"));
		roboaa[1] = new Robo(0, ggd->createModel("robo"));
		roboaa[1]->setPosition(Vector3D(0, 0, -10));
		stageaa = ggd->createModel("draw");
		gCamera = new Camera();
		JoyPad::Create();
		cout << "===loadEnd===" << endl;
	}
	gFirstFrame = false;

	Vector3D targetPosition = roboaa[0]->getPosition();
	Vector3D targetVec;
	targetVec.setSub(targetPosition, gCamera->getPosition());



	roboaa[0]->setAngleY(pangle + 180);
	roboaa[0]->update(roboaa[1]->getPosition(), targetVec);
	targetPosition = roboaa[0]->getPosition();
	gCamera->setPosition(Vector3D((5.0 - eyeZoom)*sin(pangle) + targetPosition.x, 5.0 + targetPosition.y, (5.0 - eyeZoom)*cos(pangle) + targetPosition.z));
	gCamera->setTarget(targetPosition);


	ostringstream oss;
	oss << targetVec.x << ";" << targetVec.y << ";" << targetVec.z;
	drawDebugString(10, 0, oss.str().c_str());


	Matrix44 pvm;
	gCamera->createProjectionViewMatrix(&pvm);
	roboaa[0]->draw(pvm,lightVector,lightColor,ambient);
	roboaa[1]->draw(pvm, lightVector, lightColor, ambient);
	stageaa->draw(pvm, lightVector, lightColor, ambient);
	JoyPad* j = JoyPad::getInstance();
	if (j->getZAxsis(0) < 22767) {
		pangle -= 1;
	}
	else if (j->getZAxsis(0) > 42767) {
		pangle += 1;
	}
	if (j->getRAxsis(0) < 22767) {
		eyeZoom += 0.1;
	}
	else if (j->getRAxsis(0) > 42767) {
		eyeZoom -= 0.1;
	}
	if (j->isOn(JoyPad::Button1, 0)) {
		pangle = roboaa[0]->getAngleY() + 180;
	}



	++gCount;
    ppos += 0.25;
	if (isEndRequested()) {

	}

}

