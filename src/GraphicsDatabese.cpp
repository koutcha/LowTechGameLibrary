#include "GraphicsDatabase.h"
#include "Document.h"
#include "Element.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Batch.h"
#include "Texture.h"
#include "TreeTemplate.h"
#include "Tree.h"
#include "Animation.h"
#include "Model.h"
#include "GameLib\GameLib.h"
using namespace GameLib;
GraphicsDatabase::GraphicsDatabase(const char * filename)
{
	cout << "===GraphicDatabase =====" << endl;
	Document document(filename);
	const Element* root = document.getRootElement();
	int elementNumber = root->getChildNumber();
	cout << "root children Number:" << elementNumber << endl;
	for (int i = 0; i < elementNumber; ++i) {
		const Element* e = root->getChild(i);
		const string *name= e->getName();
		if (*name == "VertexBuffer") {
			cout << "vartexLoad" << endl;
			vertexBuffers.push_back(new VertexBuffer(e));
		}
		else if (*name == "IndexBuffer") {
			cout << "indexLoad" << endl;
			indexBuffers.push_back(new IndexBuffer(e));
		}
		else if (*name == "Batch") {
			cout << "batchLoad" << endl;
			batches.push_back(new Batch(e, this));
		}
		else if (*name == "Texture") {
			cout << "textureLoad" << endl;
			textures.push_back(new MyTexture(e));
		}
		else if (*name == "Animation") {
			cout << "animationLoad" << endl;
			animations.push_back(new Animation(*e));
		}
		else if (*name == "Tree") {
			cout << "TreeLoad" << endl;


			treeTemplates.push_back(new TreeTemplate(*e,*this));
		}
	}
	//cout << "====dataList====" << endl;
	//for (int i = 0; i < vertexBuffers.size(); ++i) {
	//	cout << "<vertexBuffer>name = " << vertexBuffers[i]->getName()->c_str() << endl;
	//	cout << "size = " << vertexBuffers[i]->getSize() << endl;
	//	cout << vertexBuffers[i]->getDebugString()->c_str() << endl;
	//}
	//for (int i = 0; i < indexBuffers.size(); ++i) {
	//	cout << "<indexBuffer>name = " << indexBuffers[i]->getName()->c_str() << endl;
	//	cout << "size = " << indexBuffers[i]->getSize() << endl;
	//	cout << indexBuffers[i]->getDebugString()->c_str() << endl;
	//}
	//for (int i = 0; i < textures.size(); ++i) {
	//	cout << "<texture>name = " << textures[i]->getName()->c_str() << endl;
	//}
	//for (int i = 0; i < batches.size(); ++i) {
	//	cout << "<batch>name = " << batches[i]->getName()->c_str() << endl;
	//	cout << batches[i]->getDebugString()->c_str() << endl;
	//}
	//for (int i = 0; i < treeTemplates.size(); ++i) {
	//	cout << "<treeName>" << treeTemplates[i]->getName()->c_str() << endl;
	//	
	//}
	cout << "=========treeTemplate ====" << endl;
	
	cout << "======dataList=====" << endl;
}

GraphicsDatabase::~GraphicsDatabase()
{
	for (unsigned i = 0; i < batches.size(); ++i) {
		SAFE_DELETE(batches[i]);
	}
	for (unsigned i = 0; i < textures.size(); ++i) {
		SAFE_DELETE(textures[i]);
	}
	for (unsigned i = 0; i < vertexBuffers.size(); ++i){
		SAFE_DELETE(vertexBuffers[i]);
	}
	for (unsigned i = 0; i < indexBuffers.size(); ++i) {
		SAFE_DELETE(indexBuffers[i]);
	}
	for (unsigned i = 0; i < treeTemplates.size(); ++i) {
		SAFE_DELETE(treeTemplates[i]);
	}
	for (unsigned i = 0; i < animations.size(); ++i) {
		SAFE_DELETE(animations[i]);
	}
}

const VertexBuffer * GraphicsDatabase::getVertexBuffer(const char * name) const
{
	for (unsigned i = 0; i < vertexBuffers.size(); ++i) {
		if (*vertexBuffers[i]->getName() == name) {
			return vertexBuffers[i];
		}
	}
	return nullptr;
}

const IndexBuffer * GraphicsDatabase::getIndexBuffer(const char * name) const
{
	for (unsigned i = 0; i < indexBuffers.size(); ++i) {
		if (*indexBuffers[i]->getName() == name) {
			return indexBuffers[i];
		}
	}
	return nullptr;
}

const Batch * GraphicsDatabase::getBatch(const char * name) const
{
	for (unsigned i = 0; i < batches.size(); ++i) {
		if (*batches[i]->getName() == name) {
			return batches[i];
		}
	}
	return nullptr;
}

const MyTexture * GraphicsDatabase::getTexture(const char * name) const
{
	for (unsigned i = 0; i < textures.size(); ++i) {
		if (*textures[i]->getName() == name) {
			return textures[i];
		}
	}
	return nullptr;
}

const Animation * GraphicsDatabase::getAnimation(const char * name) const
{
	for (unsigned i = 0; i < animations.size(); ++i) {
		if (*animations[i]->getName() == name) {
			cout << "Animation return:" << animations[i]->getName()->c_str() << endl;
			return  animations[i];
		}
	}
	return nullptr;
}

Tree * GraphicsDatabase::createTree(const char * treeName) const
{
	for (unsigned i = 0; i < indexBuffers.size(); ++i) {
		if (*treeTemplates[i]->getName() == treeName) {
			return new Tree(*treeTemplates[i]);
		}
	}
	return nullptr;
}

Model * GraphicsDatabase::createModel(const char * batchName) const
{
	return new Model(getBatch(batchName));
}
