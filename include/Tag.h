#ifndef MYTAG_H
#define MYTAG_H

#include <string>
#include <vector>
using namespace std;

class Attribute;
class Tag {
public:
	enum Type {
		TYPE_BEGIN,
		TYPE_END,
		TYPE_BEGIN_TO_END,
	};
	Tag(const char* name);
	Tag(const char** readPointer, const char* end);

	const string* getName() const;
	const vector<Attribute*>* getAttributesVector() const;
	Type getTagType()const;
	

private:
	//’†g‚ÍElement‚Å”jŠü
	vector<Attribute*> attributes;
	string name;
	Type type;
	bool isNormalChar(char c);
};
#endif