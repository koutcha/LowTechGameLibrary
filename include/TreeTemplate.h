#ifndef ANIMATION_TREETEMPLATE_H
#define ANIMATION_TREETEMPLATE_H
#include<string>
using namespace std;
class Element;
class GraphicsDatabase;
class NodeTemplate;
class TreeTemplate {
public:
	TreeTemplate(const Element&,const GraphicsDatabase&);
	~TreeTemplate();
	int getNodeNumber() const;
	const NodeTemplate* getNode(int i)const;
	const string* getName() const;
private:
	int countNode(const Element&, int n);
	int build(const Element&, const GraphicsDatabase& database, int nodePos);
	string * debugString();
	NodeTemplate* _nodes;
	int _nodeNumber;
	string _name;
};
#endif
