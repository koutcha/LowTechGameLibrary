#ifndef MYTEXTURE_H
#define MYTEXTURE_H
#include<string>
namespace GameLib {
	class Texture;
}
class Element;
class MyTexture {
public:
	MyTexture(const Element*);
	MyTexture(const char* filename,const char* name);
	~MyTexture();
	void set() const; //デバイスにセット
	const std::string* getName()const;
private:
	GameLib::Texture* texture;
	std::string name;
};
#endif