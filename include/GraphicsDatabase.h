#ifndef GRAPHICSDATABASE_H
#define GRAPHICSDATABASE_H
#include <vector>
using namespace std;
class Batch;
class VertexBuffer;
class IndexBuffer;
class MyTexture;
class TreeTemplate;
class Model;
class Animation;
class Tree;
class GraphicsDatabase {
private:
	
	vector<VertexBuffer*> vertexBuffers;
	vector<IndexBuffer*> indexBuffers;
	vector<Batch*> batches;
	vector<MyTexture*> textures;
	vector<TreeTemplate*> treeTemplates;
	vector<Animation*> animations;
	int batchNumber;
	int vertexBufferNumber;
	int indexBufferNumber;
	int textureNumber;
public:
	GraphicsDatabase(const char* filename);
	~GraphicsDatabase();
	const VertexBuffer* getVertexBuffer(const char* name) const;
	const IndexBuffer* getIndexBuffer(const char* name) const;
	const Batch* getBatch(const char* name) const;
	const MyTexture* getTexture(const char* name) const;
	const Animation* getAnimation(const char* name)const;
	Tree* createTree(const char* treeName)const;
	Model* createModel(const char* batchName) const;
};
#endif