#include "Element.h"
#include "Attribute.h"
#include "Tag.h"
#include "GameLib\GameLib.h"
#include <vector>
#include <algorithm>
using namespace GameLib;
Element::Element(Tag * beginTag, const char ** p,const char* e)
{
	name = *beginTag->getName();
	cout <<"===================startTag:" <<name.c_str() << endl;
	attributes = *beginTag->getAttributesVector();
	if (beginTag->getTagType() == Tag::TYPE_BEGIN_TO_END) {
		return;
	}
	while(true) {
		
		if (*p > e) {
			//rootを抜ける
			cout << "==================endTag:" << "</ROOT>" << endl;
			break;
		}
		if (**p == '<') {
			++(*p);
			Tag tag(p,e);
			Tag::Type type = tag.getTagType();
			if (type == Tag::TYPE_BEGIN) {
				cout <<  name.c_str() <<" children pushed!"<< endl;
				children.push_back(new Element(&tag, p, e));
			}
			else if (type == Tag::TYPE_END) {
				cout << "==================endTag:" << name.c_str() << endl;
				break;
			}
			else if (type == Tag::TYPE_BEGIN_TO_END) {
				cout << "betoendTag" << endl;
				children.push_back(new Element(&tag, p, e));
			}
		}
		else {
			++(*p);
		}
	}
	cout<<"====children:" << children.size() << endl;
	for (int i = 0; i < children.size(); ++i) {
		cout << *(getChild(i)->getName())->c_str() << endl;
	}
	cout << "attribute" << attributes.size() << endl;
}
Element::~Element()
{
	
	
	cout << "デストラクト" <<  name.c_str() <<"  cn:" << children.size() <<endl;

	for (int i = 0; i < children.size(); ++i) {
		SAFE_DELETE(children[i]);
	}
	for (int i = 0; i < attributes.size(); ++i) {
		SAFE_DELETE(attributes[i]);
	}
}
const string * Element::getName() const
{
	return &name;
}

int Element::getAttributeNumber() const
{
	return attributes.size();
}



const Attribute * Element::getAttribute(int i) const
{

	ASSERT(0 <= i && i<attributes.size());
	return attributes.at(i);
}

int Element::getChildNumber() const
{
	return children.size();
}

const Element * Element::getChild(int i) const
{
	ASSERT(0<= i && i<children.size());
	return children[i];
}
