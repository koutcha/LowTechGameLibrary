#ifndef MYELEMENT_H
#define MYELEMENT_H
#include <string>
#include <vector>
using namespace std;
class Tag;
class Attribute;
class Element {
private:
	std::vector<Attribute*> attributes;
	std::vector<Element*> children;
	string name;
public:
	Element(Tag* beginTag, const char** p,const char* e);
	~Element();
	const string* getName() const;
	int getAttributeNumber() const;
	const Attribute* getAttribute(int i) const;
	int getChildNumber() const;
	const Element* getChild(int i) const;
};
#endif