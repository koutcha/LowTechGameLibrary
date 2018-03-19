#include "Library\Stage.h"
#include "Library\Matrix44.h"
#include "Library\Rectangle.h"
#include "GameLib\GameLib.h"
#include "GameLib\Framework.h"
using namespace GameLib;
Stage::Stage(Rectangle* rect):
	rect(rect),
	texture(0)
{
	Framework::instance().createTexture(&texture, "test.dds");
}
Stage::Stage(Rectangle * rect, GameLib::Texture * texture):
	rect(rect),
	texture(texture)
{
}

Stage::~Stage()
{
	Framework f = Framework::instance();
	f.destroyTexture(&texture);
	rect->~Rectangle();
}

void Stage::draw(Matrix44 & pvm)
{
	double uv[4][2] = {
		{ 0.0,0.0 },
		{ 0.0,1.0 },
		{ 1.0,0.0 },
		{ 1.0,1.0 }
	};


	rect->draw(pvm, uv,texture);

}


