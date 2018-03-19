#include "Texture.h"
#include "GameLib\Framework.h"
#include "Element.h"
#include "Attribute.h"
#include <string>
using namespace std;
using namespace GameLib;
MyTexture::MyTexture(const Element * e):
	texture(0)
{
	int attributeNum = e->getAttributeNumber();
	for (int i = 0; i < attributeNum; ++i) {

		Attribute a = *e->getAttribute(i);
		if (*a.getName() == "name") {
			name = *a.getValue();
		}
		else if( *a.getName() == "filename"){
			Framework f = Framework::instance();
			f.createTexture(&texture,a.getValue()->c_str());
		}

	}
}

MyTexture::MyTexture(const char* filename,const char* Aname):
	name(Aname),
	texture(0)
{
	Framework f = Framework::instance();
	f.createTexture(&texture, filename);
}

MyTexture::~MyTexture()
{
	Framework f = Framework::instance();
	f.destroyTexture(&texture);
}

void MyTexture::set()const
{
	Framework f = Framework::instance();
	f.setTexture(texture);
}

const string* MyTexture::getName() const
{
	return &name;
}


