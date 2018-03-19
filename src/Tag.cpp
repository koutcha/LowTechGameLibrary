#include "Tag.h"
#include "Attribute.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
Tag::Tag(const char * name):
	name(name),
	type(TYPE_BEGIN)
{
}

Tag::Tag(const char ** p, const char * e):
	type(TYPE_BEGIN)
{
	int mode = 0;
	string attributeName;
	string attributeValue;
	bool end = false;
	cout << "startTagSequence" << endl;
	while (*p < e) {
		char c = **p;
		++(*p);
		switch (mode) {
		case 0:
			switch (c)
			{
			case '/':
				type = TYPE_END;
				cout << "Tag:" << "TYPE_END" << endl;
				break;
			default:
				mode = 1;
				name += c;
				break;
			}
			break;
		case 1:
			if (c == '>') {
				end = true;
				cout << "mode1>" << endl;
			}
			else if (isNormalChar(c)) {

				name += c;
				//cout<< "name:" << name.c_str() << endl;
				if (type == TYPE_END) {
					//cout << "name:" << name.c_str() << ":endtag" <<endl;
				}
			}
			else {
				mode = 2;
			}
			break;
		case 2:
			if (c == '>') {
				end = true;
				//cout << "mode2>" << endl;
			}
			else if (isNormalChar(c)) {
				cout << "<element>" << name.c_str() <<endl;
				attributeName += c;
				mode = 3;
			}
			else if (c == '/') {
				type = Tag::TYPE_BEGIN_TO_END;
			}
			break;
		case 3:
			if (c == '=') {
				mode = 4;
			}
			else if (isNormalChar(c)) {
				attributeName += c;
				
			}
			break;
		case 4:
			if (c == '"') {
				mode = 5;
			}
			//追加
			else if(isNormalChar(c))
			{
				attributeValue += c;
				mode = 6;
			}
			break;
		case 5:
			if (c == '"') {
				mode = 2;
				//アトリビュート追加処理↓
				cout <<":"<<"<attribute>"<< attributeName.c_str() <<"=" <<  attributeValue.c_str() <<endl;
				attributes.push_back(
					new Attribute(attributeName.c_str(),attributeValue.c_str()));
				//アトリビュート追加処理↑
				attributeName.clear();
				attributeValue.clear();
			}
			else if (isNormalChar(c)) {
				attributeValue += c;
			}

			break;
		case 6:
			if (c == '\n') {
				mode = 2;
				//アトリビュート追加処理↓
				cout << ":" << "<attribute>" << attributeName.c_str() << "=" << attributeValue.c_str() << endl;
				attributes.push_back(
					new Attribute(attributeName.c_str(), attributeValue.c_str()));
				//アトリビュート追加処理↑
				attributeName.clear();
				attributeValue.clear();
			}
			else if (c == ' ') {
				mode = 2;
				//アトリビュート追加処理↓
				cout << ":" << "<attribute>" << attributeName.c_str() << "=" << attributeValue.c_str() << endl;
				attributes.push_back(
					new Attribute(attributeName.c_str(), attributeValue.c_str()));
				//アトリビュート追加処理↑
				attributeName.clear();
				attributeValue.clear();
			}
			else if (isNormalChar(c)) {
				attributeValue += c;
			}
			else if (c == '/') {
				type = Tag::TYPE_BEGIN_TO_END;
			}
			else if (c == '>') {
				cout << ":" << "<attribute>" << attributeName.c_str() << "=" << attributeValue.c_str() << endl;
				attributes.push_back(
					new Attribute(attributeName.c_str(), attributeValue.c_str()));
				//アトリビュート追加処理↑
				attributeName.clear();
				attributeValue.clear();
				end = true;
			}
			break;
		}
		if (end) {
			break;
		}
	}
	cout << "endTagSequence" << endl;
}

const string * Tag::getName() const
{
	return &name;
}

const vector<Attribute*>* Tag::getAttributesVector() const
{
	return &attributes;
}

Tag::Type Tag::getTagType() const
{
	return type;
}

bool Tag::isNormalChar(char c)
{
	if (47 < c&&c < 58|| 64<c&&c<91 || 96<c&&c<123) {
		return true;
	}
	else {
		if (c == '_' ||c=='-'||c==','||c=='.') {
			return true;
		}
		return false;
	}
}
