#include "Document.h"
#include "Element.h"
#include "GameLib\GameLib.h"
#include "Tag.h"
#include "File.h"
using namespace GameLib;
Document::Document(const char * xmlFileName)
{
	File file(xmlFileName);
	
	Tag tag("<Root>");
	const char* begin = file.getData();
	root = new Element(&tag,&begin, file.getData() + file.getFileSize());
	cout << "==============end_document" << endl;
}

Document::~Document()
{
	SAFE_DELETE(root);
}

const Element * Document::getRootElement() const
{
	return root;
}
