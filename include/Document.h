#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H
class Element;
class Document {
private:
	Element* root;
public:
	Document(const char* xmlFileName);
	~Document();
	const Element* getRootElement() const;
};
#endif
